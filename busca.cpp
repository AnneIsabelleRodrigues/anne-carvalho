#include "busca.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

Termo::Termo(){
    placing_ = new Content;
}

Termo::Termo(string s, int i){
    placing_ = new Content;
    placing_->palavra_ = s;
    placing_->docs_.insert(pair<int,int>(i,1));
    };

string Termo::RetornaPalavra(){
    return placing_->palavra_;
}

int Termo::RetornaDoc(int i){
    map<int,int>::iterator it  = placing_->docs_.find(i);
    if(it!= placing_->docs_.end())
        return i;
    else
        return 0;
}

int Termo::RetornaFreq(int i){
    return placing_->docs_.at(i);
}

Index::Index(){

}

Index::Index(Termo x){
    table_.push_back(x);
}

int Index::size(){
    return table_.size();
}

Termo Index::GetTermo(int i){
    return table_[i];
}

void Index::visuallete(){
    string s;

    for(int i = 0; i < 20; i++){
        s = table_[i].RetornaPalavra();
        cout << s << endl;
    }
}