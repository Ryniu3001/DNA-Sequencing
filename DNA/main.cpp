#include "graf.hpp"
#include "alg.hpp"
#include "Loader.h"
#include "Greedy.h"

using namespace std;

int main()
{
	clock_t start, stop;
	vector<string> data = Loader::readFromFile();
	GraphClass::vertex = data.size();
    Graph.create();
	Graph.calculateWeight(data);

	//	Graph.print();
	//	Loader::showTime(start, stop);

	/////////////////  GREEDY ///////////////////
	//Greedy GR;
	//GR.start(0, 0);
	//GR.printResult();

	/////////////////  GENETIC ///////////////////
	GeneticClass Genetic;
    Genetic.Interface();

	cin.get();
    return 0;
}


