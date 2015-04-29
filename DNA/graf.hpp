#ifndef graf_hpp
#define graf_hpp
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include "Loader.h"

using namespace std;

class GraphClass{
public:
	static const int DEPTH = 1;
    static int vertex;    
	static vector<vector<int>> matrix;
    void create();			//Tworzenie grafu
    void print();			//Wypisanie grafu na ekran
	void calculateWeight(const vector<string> &data); //wyznaczanie wag dla krawedzi
    ~GraphClass();			// Destruktor
};
extern GraphClass Graph;
#endif 
