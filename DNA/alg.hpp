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
	vector<vector<int>> chromosom;
	vector<vector<int>> children;
    vector<int> ratings;

	list<int> head;	
    void CreateList();
    int removeFromList(int a);
	void PrintList();

	int lc; // populacja
	int bestScoreInAll;
	int bestChromosomInAll;

	void DrawingPopulation(int liczbaChromosomow);
    int Rating(int liczbaChromosomow, int *bestChromosom);
	void Crossover(int par1, int par2, vector<int> child1, vector<int> child2);
	void Mutation(vector<int> chomosome);
    int TournamentSelection(int x,int liczbaChromosomow); //x - liczba chromosow w turnieju
	
public:
    void Interface();
    ~GeneticClass();
};



#endif // alg_hpp
