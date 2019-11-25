#define  DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#include "maquina_de_busca.h"
#include "indice_invertido.h"
#include "doctest.h"

using std::string;

TEST_SUITE("Indice Invertido") {
    TEST_CASE("tratar()"){
        string f = "VOCE?";
        string z = "BBBB";
        string outf = IndiceInvertido::tratar(f);
        string outz = IndiceInvertido::tratar(z);
        CHECK(outf =="voce");
        CHECK(outz =="bbbb");

        string a = "aa-aa";
        string b = "bb";
        string outa = IndiceInvertido::tratar(a);
        string outb = IndiceInvertido::tratar(b);
        CHECK(outa == "aa");
        CHECK(outb == "bb");
    }

}

TEST_SUITE("Maquina de Busca") {

    TEST_CASE("produto_interno()"){
        vector<float> q;
        vector<float> d;
        d = {1, 2, 3};
        q = {1, 5, 7};

        float out = MaquinaDeBusca::produto_interno(q, d);
        CHECK( out == (32));  
    }

    TEST_CASE("norma"){
        vector<float> v;
        v = {4, 4, 2};
        float out = MaquinaDeBusca::norma(v);
        CHECK(out == (6));
    }

    TEST_CASE("similaridade"){
        float Q,D,QD;
        Q=6;
        D=9;
        QD=10;
        float out = MaquinaDeBusca::similaridade(Q,D,QD); 
        CHECK( out == (0.18518));
    }

}
