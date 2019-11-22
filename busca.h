#include <string>
#include <map>
#include <vector>

using namespace std;


struct Conteudo;

class Termo {

    public:

    Termo();

    Termo(string s, int i);

    string RetornaPalavra();

    bool VerificaDoc(int i);

    int RetornaFreq(int i);

    void AumentaFreq(int i);

    void InserirMap(int i);

    int ocorrencias();

    ~Termo();

    private:

    Conteudo* lista_;

    int ocorrencias_;

    friend class Teste;
   
};