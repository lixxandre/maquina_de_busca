#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <set>
#include <sstream>

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



