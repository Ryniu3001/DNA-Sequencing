#ifndef graf_hpp
#define graf_hpp

#include <vector>

using namespace std;

class GraphClass{
public:
	static const int DEPTH = 4;
    static int vertex;    
    static int **matrix;
    void create();			//Tworzenie grafu
    void print();			//Wypisanie grafu na ekran
	void calculateWeight(const vector<string> &data); //wyznaczanie wag dla krawedzi
    ~GraphClass();			// Destruktor
};
extern GraphClass Graph;
#endif // graf_hpp
