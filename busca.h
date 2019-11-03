#include <string>
#include <vector>
#include <map>

using namespace std;

struct Content{

    string palavra_;
    map<int,int> docs_;
};

class Termo {
    public:
    Termo();

    Termo(string s, int i);

    string RetornaPalavra();

    int RetornaDoc(int i);

    int RetornaFreq(int i);

    private:

    Content* placing_;
   
};

class Index {
    public:
    
    Index();

    Index(Termo x);

    int size();

    Termo GetTermo(int i);

    void visuallete();

    private:

    vector<Termo> table_;
};