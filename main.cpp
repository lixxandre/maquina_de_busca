#include "indice_invertido.h"
#include "maquina_de_busca.h"


#include <sstream>      // std::istringstream
#include <iterator>     // std::istream_iterator
#include <iostream>

using namespace std;

void print_indice_invertido(map<string, vector<int> > const &mapa){
    for (auto const& pair: mapa) {
        std::cout << "{" << pair.first << ": ";
        for (auto i = pair.second.begin(); i != pair.second.end(); ++i){
          cout << *i << ' ';
        }
        cout << "} \n";

    }
}

int main(){
    
    //Recebendo nome dos arquivos
    string entrada;
    cout << "Digite o nome dos arquivos separados por espaço (incluindo a extensão de cada um)" << endl; 
    getline(cin, entrada);

    istringstream iss(entrada);
    vector<string> file_names{
        std::istream_iterator<string>(iss), {}
    };

    //Criando indice invertido vazio 
    IndiceInvertido indice_invertido(file_names);    

    vector<string>::iterator arquivo = file_names.begin();  
    int id_doc = 1;

    //Inserindo cada arquivo no indice invertido
    for(arquivo; arquivo != file_names.end(); arquivo++){
        indice_invertido.inserir(*arquivo, id_doc);
        id_doc++;
    }    
    
    //Recebendo uma consulta e fazendo dela um arquivo
    string consulta;
    ofstream arquivo_consulta;
    arquivo_consulta.open("busca.txt");
    
    
    
    cout << "Digite digite as palavras da consulta separadas por espaço" << endl;    
    getline(cin, consulta);

    

    istringstream iss2(consulta);
    vector<string> querry{
        std::istream_iterator<string>(iss2), {}
    };
    arquivo_consulta << consulta;

    //Inserindo o arquivo de busca no indice invertido
    indice_invertido.inserir("busca.txt", file_names.size()+1);

    //Criando uma maquina de busca para o Indice Invertido
    MaquinaDeBusca maquina_de_busca(indice_invertido);
    

    maquina_de_busca.cos_ranking(indice_invertido);

}