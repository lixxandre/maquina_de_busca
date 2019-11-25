#include "indice_invertido.h"


using std::map;
using std::vector;

IndiceInvertido::IndiceInvertido(vector<string> nomes_arquivos){
    file_names = nomes_arquivos;
    N_docs = file_names.size();
    
    vector< map<string, int> > vetor(N_docs+2);
    doc_Px_freq = vetor; 
}

string IndiceInvertido::tratar(string str){
    string palavras;
    char temp;
    int n = str.length();

    for (int i = 0; i < n; i++){
        temp = tolower(str[i]); // funcao para converter para minisculo
        if ((temp >= 'a' && temp <= 'z') || (temp >= '0' && temp <= '9')){
          if(temp == '-'){
            temp = ' ';
          }
            palavras.push_back(temp);
        }
    }
    return palavras;
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
  
    //extraindo as palavras do arquivo
    while (file >> palavra){         
        tratada = tratar(palavra);
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
