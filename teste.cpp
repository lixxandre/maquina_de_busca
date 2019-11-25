#define  DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#include "maquina_de_busca.h"
#include "doctest.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <cmath>

using std::string;

TEST_SUITE("MaquinaDeBusca") {
    TEST_CASE("Tratamento"){
        string f = "VOCE?";
        string z = "BBBB";
        MaquinaDeBusca::Tratamento(f);
        MaquinaDeBusca::Tratamento(z);
        CHECK(f =="voce");
        CHECK(z =="bbbb");
    }

    TEST_CASE("ler_arquivo"){}

    TEST_CASE("split"){
        string f = "aa-aa";
        string z = "bb.bb";
        MaquinaDeBusca::Tratamento(f);
        MaquinaDeBusca::Tratamento(z);
        CHECK(f == "aa aa");
        CHECK(z == "bb bb");
    }

    TEST_CASE("importanciaMap"){}

    TEST_CASE("frequenciaCount"){}

    TEST_CASE("calc_importancia"){
        float N = 5;
        float nx = 2;
        float x;
        MaquinaDeBusca::calc_importancia(N,nx);
        CHECK(x == (0,39794));

        N = 4;
        nx = 2;
        CHECK(MaquinaDeBusca::calc_importancia(N,nx) == (0.30103));
    }

    TEST_CASE("vetorDoc"){}

    TEST_CASE("produto_interno"){
        vector<float> q;
        vector<float> d;
        d = {1, 2, 3};
        q = {1, 5, 7};
        CHECK(MaquinaDeBusca::produto_interno(q, d); == (32));  
    }

    TEST_CASE("norma"){
        vector<float> v;
        v = {4, 4, 2};
        MaquinaDeBusca::norma(v);
        CHECK(norma(v) == (6));
    }

    TEST_CASE("similaridade"){
        float Q,D,QD;
        Q=6;
        D=9;
        QD=10
        CHECK(MaquinaDeBusca::similaridade(Q,D,QD) == (0.18518))
    }
}
