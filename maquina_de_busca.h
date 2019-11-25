#ifndef NOVA_MAQUINA_DE_BUSCA_H
#define NOVA_MAQUINA_DE_BUSCA_H

#include "indice_invertido.h"

#include <map>
#include <vector>
#include <numeric>      // std::accumulate
#include <math.h>
#include <iostream>
#include <algorithm> //sort


class MaquinaDeBusca{
    private:
        map<string, float> mapa_importancia;
        vector< vector<float> > space_doc;

    public:
        MaquinaDeBusca(IndiceInvertido indice_invertido);
        
        //calcula o produto interno entre dois vetores
        float produto_interno(vector<float> &Q, vector<float> &D);

        float norma(vector<float> &v);

        //calcula a similaridade entre um vetor de busca e um vetor documento        
        float similaridade(float normaQ, float normaD, float QdotD);
        
        void cos_ranking(IndiceInvertido indice_invertido); 

        ~MaquinaDeBusca();



};


#endif 