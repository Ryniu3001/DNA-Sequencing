#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "graf.hpp"
#include "alg.hpp"
#include "Loader.h"
#include "Greedy.h"

using namespace std;
vector<string> Loader::data = initializer_list<string>();


int main()
{
	clock_t start, stop;

	Loader::readFromFile();
	GraphClass::vertex = Loader::data.size();
    Graph.create();


	start = std::clock();
	Graph.calculateWeight(Loader::data);
	stop = std::clock();
	//Graph.print();
	Loader::showTime(start, stop);

	/////////////////  GREEDY ///////////////////
	Greedy GR;
	GR.start(0, 0);
	GR.printResult();

	/////////////////  GENETIC ///////////////////
	GeneticClass Genetic;
    Genetic.Interface();
    return 0;
}


