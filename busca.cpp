#include "busca.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

struct Conteudo{

    string palavra_;
    map<int,int> docs_;

};

Termo::Termo(){
    lista_ = new Conteudo;
    ocorrencias_ = 0;
}

Termo::Termo(string s, int i){
    lista_ = new Conteudo;
    lista_->palavra_ = s;
    lista_->docs_.insert(pair<int,int>(i,1));
    ocorrencias_ = 1;
    };

string Termo::RetornaPalavra(){
    return lista_->palavra_;
}

bool Termo::VerificaDoc(int i){
    auto itr = lista_->docs_.find(i);
    if(itr != lista_->docs_.end())
        return true;
    else
        return false;
}

int Termo::RetornaFreq(int i){
    auto itr = lista_->docs_.find(i);
    if(itr != lista_->docs_.end())
        return lista_->docs_.at(i);
    else
        return 0;
}

void Termo::AumentaFreq(int i){
    auto itr = lista_->docs_.find(i);
    if(itr != lista_->docs_.end()){
        int num  = itr->second;
        lista_->docs_[i] = num+1;
    }
}

void Termo::InserirMap(int i){
    lista_->docs_.insert(pair<int,int>(i,1));
    ocorrencias_++;
}

int Termo::ocorrencias(){
    return ocorrencias_;
}

Termo::~Termo(){
    lista_->palavra_.clear();
    for(auto itr = lista_->docs_.begin(); itr != lista_->docs_.end(); itr++){
        lista_->docs_.erase(itr);
        ocorrencias_--;
    }
    delete lista_;
}
