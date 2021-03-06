#ifndef alg_hpp
#define alg_hpp

#include "Loader.h" //Do testow
#include "Saver.h"
#include "graf.hpp"
#include <iostream>
#include <ctime>
#include <list>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class GeneticClass{
private:
	vector<vector<int>> chromosom;
	vector<vector<int>> children;
	vector<int> ratings;
	vector<int> path;
	vector< vector < vector<int> > > nastepniki;	// [0] -> wierzcholek [1] -> przesuniecie

	list<int> createList(vector<int> chromosome);
	int removeFromList(int a, list<int> lista);
	void printList(list<int> lista);

	int lc; // populacja, liczba chromosomow
	int bestScoreInAll;

	void initializeVectors();
	void generateNastepniki();
	void DrawingPopulation();
	int Rating();
	void Crossover(int par1, int par2, vector<int> &child1, vector<int> &child2);
	void repair(vector <int> &chrom1, vector<int> &chrom2);
	void Mutation(vector<int> &chomosome);
	void makeBetterMutation(vector<int> &chromosome);
	int TournamentSelection(int x);		//x - liczba chromosow w turnieju
	void showBest();
	int printBest();

	void checksRepeatsInSet();
	void createChromosom(int j, vector <bool> &visited, vector<int> &chrom, int dnaLen, bool random);

public:
	void Interface();
	~GeneticClass();
};



#endif // alg_hpp
