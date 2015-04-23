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
	vector<int> path;
	vector<vector<int>> chromosom;
	vector<vector<int>> children;
    vector<int> ratings;

	list<int> head;	
    void CreateList();
    int removeFromList(int a);
	void PrintList();

	int lc;						 // populacja - liczba chromosomów
	int bestScoreInAll;
	int bestChromosomInAll;
	int bestChromosom;
	void initializeVectors();

	void DrawingPopulation(int liczbaChromosomow);
    int Rating();
	void Crossover(int par1, int par2, vector<int> child1, vector<int> child2);
	void Mutation(vector<int> chomosome);
    int TournamentSelection(int x,int liczbaChromosomow); //x - liczba chromosow w turnieju
	void showBest();
	
public:
    void Interface();
    ~GeneticClass();
};



#endif // alg_hpp
