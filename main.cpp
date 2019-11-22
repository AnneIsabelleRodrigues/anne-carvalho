#include <iostream>
#include <fstream>
#include <list>
#include <math.h>
#include <algorithm>
#include "busca.h"
#define MAX 15

using namespace std;

int main(){
    list <Termo> Index;
    string palavra, novapalavra, pesquisa, novapesquisa, maiordoc;
    string q[MAX];
    string f[MAX];
    int NFILES = 0;
    int verificacao, contagem = 0, tamq = 0;
    float tf, idf, W;
    vector<float> search;
    float acumsup = 0, acuminf, sumD = 0, sumQ = 0, maior;
    char again = 's';

    ifstream entrada;
    entrada.open("consulta.txt", ios::in);
    while(!entrada.eof()){
        entrada >> f[NFILES];
        NFILES++;
    }
    entrada.close();

    vector<float> similaridade (NFILES);

    for(int i = 0; i < NFILES; i++){
        ifstream files;
        files.open(f[i].c_str(),ios::in);
        while(!files.eof()){
            files >> palavra;
            transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower);
            for(string::iterator it = palavra.begin(); it != palavra.end(); ++it){
                if((*it >= 'a' && *it <= 'z') || (*it >= '1' && *it <= '9')){
                    novapalavra += *it;
                }
            }
            verificacao = 0;
            for (auto itr = Index.begin(); itr != Index.end(); itr++){
                if(((itr->RetornaPalavra()).compare(novapalavra)) == 0){
                    verificacao++;
                    if(itr->VerificaDoc(i) == true){
                        itr->AumentaFreq(i);
                    }
                    else if(itr->VerificaDoc(i) == false){
                        itr->InserirMap(i);
                    }
               }
            }
            if(verificacao == 0){
                Termo* x = new Termo(novapalavra,i);
                Index.push_back(*x);
            }
            novapalavra.clear();
        }
        files.close();
    }

    vector< vector<float> > coordenadas(Index.size(),vector<float>(NFILES));

    for (auto itr = Index.begin(); itr != Index.end(); itr++){
        contagem++;
        for(int j = 0; j < NFILES; j++){
            if(itr->VerificaDoc(j) == true)
                tf = itr->RetornaFreq(j);
            else
                tf = 0.00;
            idf = log(NFILES/itr->ocorrencias());
            W = tf*idf;
            coordenadas[contagem-1][j] = W;
        }
    }

    cout << "Entre com sua pesquisa: ";
    getline(cin,pesquisa, ' ');
    while(pesquisa.compare("0") != 0){
        transform(pesquisa.begin(), pesquisa.end(), pesquisa.begin(), ::tolower);
        for(string::iterator it = pesquisa.begin(); it != pesquisa.end(); ++it){
            if((*it >= 'a' && *it <= 'z') || (*it >= '1' && *it <= '9')){
                novapesquisa += *it;
            }
        }
        q[tamq] = novapesquisa;
        tamq++;
        novapesquisa.clear();
        getline(cin,pesquisa, ' ');
    }

    for (auto itr = Index.begin(); itr != Index.end(); itr++){
        tf = 0;
        for(int i = 0; i < tamq; i++){
            if((itr->RetornaPalavra()).compare(q[i]) == 0){
                tf++;
            }
        }
        idf = log(NFILES/(itr->ocorrencias()));
        W = idf * tf;
        search.push_back(W);
    }

    for(int j = 0; j < NFILES; j++){
    acumsup = 0;
    sumD = 0;
    sumQ = 0;
        for(int i = 0; i < tamq; i++){
            contagem = 0;
            for (auto itr = Index.begin(); itr != Index.end(); itr++){
                contagem++;
                if((itr->RetornaPalavra()).compare(q[i]) == 0){
                    acumsup = acumsup + (coordenadas[contagem-1][j] * search[contagem-1]);
                    sumD = sumD + pow(coordenadas[contagem-1][j],2);
                    sumQ = sumQ + pow(search[contagem-1],2);
                }
            }
        }
        acuminf = sqrt(sumD) * sqrt(sumQ);
            if(acuminf > 0 )
                similaridade[j] = acumsup/acuminf;
            else
                similaridade[j] = 0;
    }

    cout << endl;
    cout << "         *************************************" << endl;
    cout << "          RANKING" << "          " << "       DOCUMENTO" << endl;  
    for(int i = 0; i < NFILES; i++){
        maior = -1000;
        for(int j = 0; j < NFILES; j++){
            if(similaridade[j] > maior){
                maior  = similaridade[j];
                maiordoc = f[j];
                contagem = j;
            }
        }
        similaridade[contagem] = -1000;
        cout << "             "  << i+1 << "                   " << maiordoc << endl;
    }

    cout << "         *************************************" << endl;

    return 0;
}