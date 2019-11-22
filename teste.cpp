#define  DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#include "maquina_de_busca.h"
#include "doctest.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <cmath>

using std::string;

TEST_SUITE("MaquinaDeBusca"){
    TEST_CASE("Tratamento(string)"){
        string x = "B1";
        string saida = MaquinaDeBusca::Tratamento(x);
        CHECK(saida == "b");
        x = "33";
        saida = MaquinaDeBusca::Tratamento(x);
        CHECK(saida == "3"); 
    }

    TEST_CASE("ler_arquivo(string)"){
    }

    TEST_CASE("calc_importancia()"){

        int x= MaquinaDeBusca::calc_importancia(2,1);
        CHECK(x == 3);
        
        x = MaquinaDeBusca::calc_importancia(4,2);
        CHECK(x == 3);
    }

    TEST_CASE("produto_interno(vector)"){

    }
/*
    TEST_CASE("norma(vector)"){
        vector<float> v { 1, 2, 3};
        CHECK(MaquinaDeBusca::norma(v) == 14);
    }

    TEST_CASE("similaridade()"){
        float normaQ, normaD, QdotD;
        
        QdotD = 9;
        normaQ = (3*(sqrt(2)));
        normaD = 3;
        float x = MaquinaDeBusca::similaridade(normaQ, normaD, QdotD);
        CHECK(x == 2/sqrt(2));

    }
*/ 
}


