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

class MaquinaDeBusca{
    public:

        string Tratamento(string str);

        void ler_arquivo(string str);

        set<string> split(string str);


        // Px palavra
        // d_j documento j 
        // tf frequencia que a palvra Px aparece em d_j

        //(idf) importancia de Px em d_j: log(N/nx)
        float calc_importancia(int N, int nx);

        //coordenada do documento dj no eixo Pt: importancia * frequencia
        float coordenadas(int frequencia, int importancia);

        //calcula o produto interno entre dois vetores
        float produto_interno(vector<float> &Q, vector<float> &D);

        float norma(vector<float> &v);

        //calcula a similaridade entre um vetor de busca e um vetor documento
        //produto interno de (u com v) / norma(u) * norma (v)
        float similaridade(float normaQ, float normaD, float QdotD){
        return  QdotD/(normaQ * normaD);
        }

}