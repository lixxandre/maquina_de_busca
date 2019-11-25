#include "indice_invertido.h"


using std::map;
using std::vector;

IndiceInvertido::IndiceInvertido(vector<string> nomes_arquivos){
    file_names = nomes_arquivos;
    N_docs = file_names.size();
    
    vector< map<string, int> > vetor(N_docs+2);
    doc_Px_freq = vetor; 
}

string IndiceInvertido::tratar_az_09_hifem(string str){
    string palavra;
    char temp;
    int n = str.length();

    for (int i = 0; i < n; i++){
        temp = tolower(str[i]); // funcao para converter para minisculo
        if ((temp >= 'a' && temp <= 'z') || (temp >= '0' && temp <= '9')){          
          palavra.push_back(temp);
        }
        if(temp == '-'){
            temp = ' ';
            palavra.push_back(temp);
        }
    }
    return palavra;
}

//insere as palavras de um novo documento ao indice
void IndiceInvertido::inserir(const string& filename, int id_doc){
    // filestream variable file 
    fstream file; 
    string palavra;
    string tratada;
    map<string,int> dic_freq;   
    
    //abrindo o arquivo 
    file.open(filename.c_str());

    string str;
    vector<string> texto_sem_pontuacao;
    
    while (file >> str){
      str.erase(remove_if(str.begin(), str.end(), ::ispunct), str.end()); 
      //str.erase(remove(str.begin(),str.end(),'\"'),str.end());
      transform(str.begin(), str.end(), str.begin(), ::tolower);

      texto_sem_pontuacao.push_back(str);
    }

    //extraindo as palavras do arquivo
    int i;
    for(i = 0; i < texto_sem_pontuacao.size(); i++) {
      string palavra = texto_sem_pontuacao[i];

      tratada = tratar_az_09_hifem(palavra);
      if(tratada != ""){
        //incrementa frequencia da palvra no doc
        dic_freq[tratada]++;

        //palavra esta presente no documento
        if ((mapa).count(tratada) > 0){
          (mapa)[tratada][id_doc] = 1;
        }else{
          vector<int> novo(N_docs+2); 
          novo[id_doc] = 1;
          (mapa)[tratada] = novo; 
        }
      }
        
  }
  doc_Px_freq[id_doc] = dic_freq;

}

//retorna o mapa do indice invertido
map<string, vector<int> > IndiceInvertido::getMapa(){
    return mapa; 
}

//tamanho do indice (quantas palavras possui)
double IndiceInvertido::tamanho(){

}

//nro de documentos onde certa palavra ocorreu
double IndiceInvertido::frequencia(const string& palavra, int id_doc){
  return doc_Px_freq[id_doc][palavra];
}

//retorna o nro de documentos da coleção
int IndiceInvertido::get_qtd_docs(){
  return N_docs;
}

//retorna a lista dos documentos
vector<string> IndiceInvertido::listadocs(){
    return file_names; 
}

IndiceInvertido::~IndiceInvertido(){
  map<string, vector<int> >().swap(mapa);
  vector< map<string, int> >().swap(doc_Px_freq);
  vector<string>().swap(file_names);

}
