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
#include <numeric>      // std::accumulate
#include <sstream>      // std::istringstream
#include <iterator>     // std::istream_iterator
#include <set>


using namespace std;

class MaquinaDeBusca{
    public:

        static string Tratamento(string str);

        static void ler_arquivo(string str);

        static set<string> split(string str);

        //dado um vector representando o texto retorna um map com a frequencia de cada palavra no texto
        static map<string, int> frequenciaMap(vector<string> texto);

        //dado um vector representando o texto retorna um map com a importancia de cada palavra no texto
        static map<string, float> importanciaMap(vector<string> texto);


        //(idf) importancia de Px em d_j: log(N/nx)
        static float calc_importancia(int N, int nx);

        //cria vetor que representa o documento
        static vector<float> vetorDoc(map<string, int> frequencia, map<string, float> importancia, vector<string> dicionario){

        //calcula o produto interno entre dois vetores
        float produto_interno(vector<float> &Q, vector<float> &D);

        float norma(vector<float> &v);

        //calcula a similaridade entre um vetor de busca e um vetor documento
        //produto interno de (u com v) / norma(u) * norma (v)
        float similaridade(float normaQ, float normaD, float QdotD);


    }
};