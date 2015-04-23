#ifndef alg_hpp
#define alg_hpp

#include "Loader.h" //Do testow
#include "graf.hpp"
#include <iostream>
#include <ctime>
#include <list>
#include <vector>

using namespace std;

struct ListStruct{
    int value;
    ListStruct *next;
};

class GeneticClass{
private:
    short int ** chromosom;
    short int ** children;
    int *ratings;
	ListStruct *head;
	
    void CreateList();
    int removeFromList(int a);

	int lc; // populacja
	int bestScoreInAll;
	int bestChromosomInAll;

	void DrawingPopulation(int liczbaChromosomow);
    int Rating(int liczbaChromosomow, int *bestChromosom);
    void Crossover(int par1, int par2, short int child1[], short int child2[]);
    void Mutation(short int chomosome[]);
    int TournamentSelection(int x,int liczbaChromosomow); //x - liczba chromosow w turnieju

	void PrintList();

public:
    void Interface();
    ~GeneticClass();
};



#endif // alg_hpp
