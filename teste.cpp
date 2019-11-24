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
        string a = "OI";
        string b = "VOCE";
        string c = "DIA.?";

        Tratamento(a);
        Tratamento(b);
        Tratamento(c);

        CHECK(a == "oi");
        CHECK(b == "voce");
        CHECK(c == "dia");
    }
    TEST_CASE("split"){
        string a = "guarda-chuvas";
        string b = "oi.oi";
        string c = "dia-a-dia?";

        split(a);
        split(b);
        split(c);

        CHECK(a == "guardachuvas");
        CHECK(b == "oioi");
        CHECK(c == "diaadia");
    }

    TEST_CASE("frequenciaCount"){
        string a[5], b[5];
        int c = 0;
        a[0] = "oi";
        a[1] = "oi";
        a[2] = "tudo";
        a[3] = "bem";
        a[4] = "bem";

        for(int i = 0; i < 5; i++){
            b[i] = a[i];
        }

        frequenciaCount(5, a, b, c);

        CHECK(c == 2);
    }

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
