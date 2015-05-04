#ifndef alg_hpp
#define alg_hpp

#include "Loader.h" //Do testow
#include "graf.hpp"
#include <iostream>
#include <ctime>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

class GeneticClass{
private:
	vector<vector<int>> chromosom;
	vector<vector<int>> children;
	vector<int> ratings;
	vector<int> path;
	vector< vector < vector<int> > > nastepniki;

	list<int> createList(vector<int> chromosome);
	int removeFromList(int a, list<int> lista);
	void printList(list<int> lista);

	int lc; // populacja, liczba chromosomow
	int bestScoreInAll;

	void initializeVectors();
	void generateNastepniki();
	void checkPositives();
	void checkOthers();
	void DrawingPopulation();
	int Rating();
	void Crossover(int par1, int par2, vector<int> &child1, vector<int> &child2);
	void Mutation(vector<int> &chomosome);
	int TournamentSelection(int x); //x - liczba chromosow w turnieju
	void showBest();
	void printBest();

	void checksRepeatsInChromosom();
	void checksRepeatsInSet();

public:
	void Interface();
	~GeneticClass();
};



#endif // alg_hpp
