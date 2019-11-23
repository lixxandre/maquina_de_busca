#include "maquina_de_busca.h"
using namespace std;

map<string, set<string> > M;

void print_map(map<string, int> const &mapa)
{
    for (auto const& pair: mapa) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

void print_map_float(map<string, float> const &mapa)
{
    for (auto const& pair: mapa) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

void print_indice_invertido(map<string, vector<int> > const &mapa)
{
    for (auto const& pair: mapa) {
        std::cout << "{" << pair.first << ": ";
        for (auto i = pair.second.begin(); i != pair.second.end(); ++i){
          cout << *i << ' ';
        }
        cout << "} \n";

    }
}

string Tratamento(string str){
    string palavras;
    char temp;
    int n = str.length();

    for (int i = 0; i < n; i++){
        temp = tolower(str[i]); // funcao para converter para minisculo
        if ((temp >= 'a' && temp <= 'z') || (temp >= '0' && temp <= '9')){
            palavras.push_back(temp);
        }
    }
    return palavras;
}

set<string> split(string str) {
  stringstream ss(str);
  string aux;
  set<string> splittedString;
  while (getline(ss, aux, ' ')) {
    aux = Tratamento(aux);
    splittedString.insert(aux);
  }
  return splittedString;
}



//dado um vector representando o texto retorna um map com a frequencia de cada palavra no texto 
map<string, int> frequenciaCount(vector<string> texto){
  map<string, int> frequencia; 
  
  vector<string>::iterator itt = texto.begin();   
  for(itt ; itt != texto.end() ; itt++){ 
    frequencia[*itt]++;
  }

  return frequencia;
}

//(idf) importancia de Px em d_j 
float calc_importancia(int N, int nx){  
  float x = log((float)N/nx);  
  return x;              // N numero de documentos
                                // nx quantidade de documentos que a palavra Px aparece
}

/*    
//dado um vector representando o dicionario retorna um map com a importancia de cada palavra
map<string, float> importancia-Map(map<string, vector<int>> indice_invertido, int N_docs, map<string,int> n_incidencia){
  map<string, float> importancia; 
  
  vector<string>::iterator palavra = dicionario.begin();   
  for(palavra ; palavra != dicionario.end() ; palavra++){ 
    importancia[*palavra] = calc_importancia(N_docs, n_incidencia[*palavra]);
  }

  return importancia;
}
*/


//retorna um map com [ palavra x importancia cancelado: qtd de documentos que ela aparece ] 
map<string, float> importanciaMap( map<string, vector<int> > *indice_invertido, int N_docs){
  map<string, int> mapa_incidencia;
  map<string, float> mapa_importancia;
  
  for (auto const& pair: *indice_invertido) {
    mapa_incidencia[pair.first] = accumulate(pair.second.begin(), pair.second.end(), 0); //testado
    
    mapa_importancia[pair.first] = calc_importancia(N_docs, mapa_incidencia[pair.first]);

  }
  
  return mapa_importancia;
}


//calcula o produto interno entre dois vetores
float produto_interno(vector<float> &Q, vector<float> &D){
  vector<float>::iterator itq = Q.begin(); 
  vector<float>::iterator itd = D.begin(); 
  
  float dot = 0;
  for(itq, itd; itq != Q.end() && itd != D.end(); itq++, itd++){ 
    dot += (*itd) * (*itq);  
  }

  return dot;
}

float norma(vector<float> &v){
  return sqrt(produto_interno(v,v));
}

//cria vetor que representa o documento
vector<float> vetorDoc(map<string, int> frequencia, map<string, float> importancia, vector<string> dicionario){
  vector<float> D; 

  vector<string>::iterator palavra = dicionario.begin();
  for(palavra ; palavra != dicionario.end() ; palavra++){ 
    D.push_back(frequencia[*palavra] * importancia[*palavra]);
  }
  return D;
}


//calcula a similaridade entre um vetor de busca e um vetor documento
float similaridade(float normaQ, float normaD, float QdotD){
  return  QdotD/(normaQ * normaD);
}

// le arquivo e retorna um map [palavra x frequencia no arquivo]
// marca no indice invertido que a palavra está presente no arquivo
map<string,int> ler_arquivo(string filename, map<string, vector<int>> *indice_invertido, int id_doc, int N) {
    // filestream variable file 
    fstream file; 
    string palavra;
    string tratada;
    map<string,int> dic_freq;   
    
    // opening file 
    file.open(filename.c_str()); 
  
    // extracting words from the file 
    while (file >> palavra) 
    { 
        // displaying content 
        tratada = Tratamento(palavra);
        if(tratada != ""){
          //incrementa frequencia da palvra no doc
          dic_freq[tratada]++;

          //palavra esta presente no documento
          if ((*indice_invertido).count(tratada) > 0){
            (*indice_invertido)[tratada][id_doc] = 1;
          }else{
            vector<int> novo(N+1); 
            novo[id_doc] = 1;
            (*indice_invertido)[tratada] = novo; 
          }
        }
        
    }
    /*
    cout << "------INDICE INVERTIDO --------" << endl;
    print_indice_invertido(*indice_invertido);
    */
    return dic_freq;
}

bool sortcol( const vector<int>& v1, const vector<int>& v2 ) { 
 return v1[1] < v2[1]; 
} 





int main(){
  
  map<string, vector<int> > mapa;
  vector<int> vetor{0, 1, 1, 0, 1};
  mapa["coco"] = vetor;
  map <string, int > dicionario;
  
 
  // dicionario = ler_arquivo("arquivo", indice_invertido, 1,1);
  
  // cout << accumulate(dicionario1["na"].begin(), dicionario1["na"].end(),0); 
  
  
  //------------- COMEÇANDO DE VERDADE -------------- 
  map<string, vector<int> > indice_invertido;

  //recebendo nome dos arquivos
  string entrada;
  cout << "Digite o nome dos arquivos separados por espaço (incluindo a extensão de cada um)" << endl; 
  getline(cin, entrada);

  istringstream iss(entrada);
  vector<string> file_names{
    std::istream_iterator<string>(iss), {}
  };

  
  vector<string>::iterator arquivo = file_names.begin();  
  int id_doc = 1;
  
  //cada posicao representa um doc e contem um mapa[palavra x freq no doc]
  vector< map<string, int> > doc_Px_freq( file_names.size()+1) ;
  
  //abrindo cada arquivo
  for(arquivo; arquivo != file_names.end(); arquivo++){
    
    //cout << "lendo o arquivo: " <<  *arquivo << endl;
    doc_Px_freq[id_doc] = ler_arquivo(*arquivo, &indice_invertido, id_doc, file_names.size());  
    
    id_doc++;
  }

  //calculando o numero de arquivos que cada palavra aparece
  //retorna um map com [ palavra x qtd de documentos que ela aparece ] 
  //dado um vector representando o dicionario retorna um map com a importancia de cada palavra
  map<string, float> mapa_importancia;
  mapa_importancia = importanciaMap(&indice_invertido,file_names.size());

  /*
  cout << endl << "MAPA DE IMPORTANCIA" << endl; 
  print_map_float(mapa_importancia); 
  */

  //calcular o vetor para cada doc
  vector< vector<float> > space_doc(file_names.size()+1); 
  float x;
  for(id_doc = 1; id_doc <= file_names.size(); id_doc++){
    vector<float> D; 

    for (auto const& pair: indice_invertido) {
        x = doc_Px_freq[id_doc][pair.first] * mapa_importancia[pair.first] ;
        D.push_back(x);
    }
    space_doc[id_doc] = D;
  }
  
  //Recebendo uma consulta
  string consulta;
  cout << "Digite digite as palavras da consulta separadas por espaço" << endl; 
  getline(cin, consulta);

  istringstream iss2(consulta);
  vector<string> querry{
    std::istream_iterator<string>(iss2), {}
  };
  
  map<string, int> querry_Px_freq;
  int i;

  for(i = 0; i < querry.size(); i++){
    //incrimenta frequencia na pesquisa
    querry_Px_freq[ querry[i] ]++;
  }
  //criando vetor que representa a busca
  vector<float> Q; 

  float y;
  for (auto const& pair: indice_invertido) {    
    y = querry_Px_freq[pair.first] * mapa_importancia[pair.first] ;  
    Q.push_back(y);
  }
  //vetor de busca
  
  
  //classificando documentos  
  map<float, string> map;  
  

  for(id_doc = 1; id_doc <= file_names.size(); id_doc++){   
    float normaQ = norma(Q); 
    float normaD = norma(space_doc[id_doc]);
    float QdotD = produto_interno(Q, space_doc[id_doc]);

    map[similaridade(normaQ, normaD, QdotD)] = file_names[id_doc-1];
  }
  
  //exibindo a classificacao

  vector<string> final; 
  
  cout << endl << "Ranking" << endl;
  for (auto const& pair: map) {
    //cout << pair.second << endl;
    final.push_back(string(pair.second));
  }
  

  for(i = final.size()-1 ; i >= 0; i--){
    cout << final[i] << endl; 
  }
  

    
} 

