#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include "busca.h"
#define MAX 15
#define NFILES 4

using namespace std;

int main(){
    string palavra, novapalavra;
    string f[] = {"doc1.txt", "doc2.txt", "doc3.txt", "doc4.txt"};
    int k = 0;

    for(int i = 0; i < NFILES; i++){
        ifstream files;
        files.open(f[i].c_str(),ios::in);
        while(!files.eof()){
            files >> palavra;
            transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower);
            for(string::iterator it = palavra.begin(); it != palavra.end(); ++it){
                if(*it >= 'a' && *it <= 'z'){
                    novapalavra += *it;
                }
            }
            Termo x(novapalavra,i);
            Index lista(x);
            lista.visuallete();
            novapalavra.clear();
            k++;
        }
    }
    return 0;
}