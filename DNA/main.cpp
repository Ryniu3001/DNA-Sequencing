#include <iostream>
#include <stdlib.h>
#include "graf.hpp"
#include "alg.hpp"
#include "Loader.h"
#include <ctime>
#include "Greedy.h"

using namespace std;
vector<string> Loader::data = initializer_list<string>();


int main()
{
	Loader::readFromFile();
	//Loader::show();			//odwolujesz siê Loader::data[i] i musisz miec #include "Loader.h"


    cout << "Podaj liczbe wierzcholkow: ";
    
	GraphClass::vertex = Loader::data.size();
    Graph.create();

	std::clock_t    start;
	std::clock_t    stop;
	start = std::clock();
	Graph.calculateWeight(Loader::data);
	stop = std::clock();
	std::cout << "Time: " << (stop-start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
   //Graph.print();
    cout << endl;

	Greedy GR;
	GR.start(0, 0);
	GR.printResult();
/////////////////  GENETIC ///////////////////
    
	GeneticClass Genetic;
    Genetic.Interface();
    return 0;
}


