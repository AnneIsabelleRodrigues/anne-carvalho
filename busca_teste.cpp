#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "busca.h"

#include "doctest.h"

#include <iostream>

class Teste{

    public:

    static Conteudo* elemento(const Termo &a){
        return a.lista_;
    }

    static int ocorrencias(const Termo &a){
        return a.ocorrencias_;
    }
};

TEST_SUITE("Termo"){
    TEST_CASE("Termo()"){
        Termo a;
        CHECK(Teste::ocorrencias(a) == 0);
    }
    TEST_CASE("Termo(string,int)"){
        Termo a("A",1);
        CHECK((a.RetornaPalavra()).compare("A") == 0);
        CHECK(a.VerificaDoc(1) == true);
        CHECK(Teste::ocorrencias(a) == 1);
    }
    TEST_CASE("RetornaPalavra()"){
        Termo a ("A",1);
        CHECK((a.RetornaPalavra()).compare("A") == 0);
        Termo b ("K",2);
        CHECK((b.RetornaPalavra()).compare("K") == 0);
    }
    TEST_CASE("VerificaDoc(int)"){
        Termo a ("A",1);
        CHECK(a.VerificaDoc(1) == true);
        CHECK(a.VerificaDoc(2) == false);
    }
    TEST_CASE("RetornaFreq(int)"){
        Termo a ("A",1);
        CHECK(a.RetornaFreq(1) == 1);
        CHECK(a.RetornaFreq(2) == 0);
    }
    TEST_CASE("IncreaseFreq(int)"){
        Termo a ("A",1);
        CHECK(a.RetornaFreq(1) == 1);
        a.IncreaseFreq(1);
        a.IncreaseFreq(1);
        CHECK(a.RetornaFreq(1) == 3);
    }
    TEST_CASE("InserirMap(int)"){
        Termo a ("A",1);
        CHECK(Teste::ocorrencias(a) == 1);
        a.InserirMap(2);
        CHECK(Teste::ocorrencias(a) == 2);
        a.InserirMap(5);
        a.InserirMap(6);
        CHECK(Teste::ocorrencias(a) == 4);
    }
    TEST_CASE("ocorrencias()"){
        Termo a ("A",1);
        a.InserirMap(2);
        a.InserirMap(3);
        CHECK(a.ocorrencias() == 3);
    }
}// end TEST_SUITE("Termo")