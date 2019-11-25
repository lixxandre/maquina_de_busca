#ifndef INDICE_INVERTIDO_H
#define INDICE_INVERTIDO_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream> //ler aquivo
#include <algorithm>

using namespace std;

class IndiceInvertido{
    private:
        //cabe inicializar 
        int N_docs;
        vector<string> file_names;        
        vector< map<string, int> > doc_Px_freq; 
        map<string, vector<int> > mapa;

    public:
        //mantem só letras e numeros, troca ifem por espaço
        static string tratar_az_09_hifem(string str); 
        
        //cria um indice invertido vazio para os documentos passados no vetor
        IndiceInvertido(vector<string> file_names);

        //insere as palavras de um novo documento ao indice
        virtual void inserir(const string& filename, int id_doc);

        //retorna o mapa do indice invertido
        virtual map<string, vector<int> > getMapa();

        //tamanho do indice (quantas palavras possui)
        virtual double tamanho();

        //quantas vezes a palvra Px apareceu no documento d_j
        virtual double frequencia( const string& palavra, int id_doc) ;

        //retorna a quantidade de documentos da coleção
        virtual int get_qtd_docs();

        //retorna a lista dos documentos
        virtual vector<string> listadocs();
    
        ~IndiceInvertido();    
    
    
};

#endif 