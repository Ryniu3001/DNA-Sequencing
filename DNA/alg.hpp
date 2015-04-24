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
	vector<int> path;

	list<int> head;
	void CreateList();
	int removeFromList(int a);
	void PrintList();

	int lc; // populacja, liczba chromosomow
	int bestScoreInAll;
	int bestChromosomInAll;

	void initializeVectors();
	void DrawingPopulation();
	int Rating();
	void Crossover(int par1, int par2, vector<int> &child1, vector<int> &child2);
	void Mutation(vector<int> &chomosome);
	int TournamentSelection(int x); //x - liczba chromosow w turnieju
	void showBest();

	void showVector(vector< vector<int> > wektor);
	//bool rosnaco(vector<int> *const a, vector<int> *const b);
public:
	void Interface();
	~GeneticClass();
};



#endif // alg_hpp
