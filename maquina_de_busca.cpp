#include "maquina_de_busca.h"


using std::string;
using std::map;
using std::vector;

void print_map_float(map<string, float> const &mapa){
    for (auto const& pair: mapa) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

void print_map(map<string, int> const &mapa){
    for (auto const& pair: mapa) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

MaquinaDeBusca::MaquinaDeBusca(IndiceInvertido indice_invertido){
    map<string, vector<int> > mapa_indice_invertido;
    mapa_indice_invertido = indice_invertido.getMapa();
    int N_docs = indice_invertido.get_qtd_docs();
    
    int id_doc;    
    map<string, int> mapa_incidencia;
    map<string, float> importancia;


    

    //Calculando importancia
    for (auto const& pair: mapa_indice_invertido) {
        mapa_incidencia[pair.first] = accumulate(pair.second.begin(), pair.second.end(), 0);
        importancia[pair.first] = log( (float) N_docs/mapa_incidencia[pair.first] );        
    }   
    
    mapa_importancia = importancia;        
    
    space_doc.push_back({0,0,0,0,0,0});

    //Calculando vetores para cada doc    
    for(id_doc = 1; id_doc <= N_docs; id_doc++){
        vector<float> D;
        for (auto const& pair: mapa_indice_invertido) {                                               
            D.push_back( indice_invertido.frequencia(pair.first, id_doc) * mapa_importancia[pair.first] );            
        }
        
        space_doc.push_back(D);
    }
    
}


float MaquinaDeBusca::produto_interno(vector<float> &Q, vector<float> &D){
  vector<float>::iterator itq = Q.begin(); 
  vector<float>::iterator itd = D.begin(); 
  
  float dot = 0;
  for(itq, itd; itq != Q.end() && itd != D.end(); itq++, itd++){ 
    dot += (*itd) * (*itq);  
  }

  return dot;
}

float MaquinaDeBusca::norma(vector<float> &v){
  return sqrt(produto_interno(v,v));
}


float MaquinaDeBusca::similaridade(float normaQ, float normaD, float QdotD){
  return  QdotD/(normaQ * normaD);
}

bool sortbysec(const pair<string,float> &a, const pair<string,float> &b){ 
    return (a.second > b.second); 
} 

void MaquinaDeBusca::cos_ranking( IndiceInvertido indice_invertido ){        
    int N_docs = indice_invertido.get_qtd_docs();
    vector<string> file_names = indice_invertido.listadocs();
    
    vector<float> Q = space_doc[N_docs];
    
    map<string, float> map;  
    int id_doc;
    
    
    
    for(id_doc = 1; id_doc <= N_docs; id_doc++){   
        float normaQ = norma(Q); 
        float normaD = norma(space_doc[id_doc]);
        float QdotD = produto_interno(Q, space_doc[id_doc]);

        map[file_names[id_doc-1]] = similaridade(normaQ, normaD, QdotD);
    }

    
    //exibindo a classificacao
    vector< pair<string,float> > rank; 
    rank.assign(map.begin(), map.end());
    sort(rank.begin(), rank.end(), sortbysec); 
    
    cout << endl << "Ranking" << endl;
    for (id_doc =0; id_doc < N_docs; id_doc++){

        cout << rank[id_doc].first << endl;
    } 

}

MaquinaDeBusca::~MaquinaDeBusca(){

}
