#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <set>
#include <sstream>
#include <math.h>

using namespace std;

map<string, set<string> > M;

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

void ler_arquivo(string str) {
    ifstream ifs;
    string temp;

    cout << "Lendo arquivo " << str  << endl;
    ifs.open(str.c_str());

    if(ifs.is_open()) {
    while(!ifs.eof()) {
      ifs >> temp;
      temp = Tratamento(temp);
      if(temp.length() >= 1) {
        M[temp].insert(str);
      }
    }
  } else {
    cout << "Arquivo nao encontrado" << endl;
  }
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


// Px palavra
// d_j documento j 
// tf frequencia que a palvra Px aparece em d_j



//(idf) importancia de Px em d_j 
float calc_importancia(int N, int nx){  
  return log(N/nx);              // N numero de documentos
                                // nx quantidade de documentos que a palavra Px aparece
}

//coordenada do documento dj no eixo Pt
float coordenadas(int frequencia, int importancia){
  return frequencia * importancia;                    //frequencia da palavra Pt no documento dj
                                                      //importancia de Pt na coleção
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

//calcula a similaridade entre um vetor de busca e um vetor documento
float similaridade(float normaQ, float normaD, float QdotD){
  return  QdotD/(normaQ * normaD);
}



int main(){
  int N = 2;

  vector<float> v(N);
    for (int i=0; i<N; i++)
        cin >> v[i];
    cout << norma(v);
    
} 

