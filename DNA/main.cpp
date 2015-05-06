#include "graf.hpp"
#include "alg.hpp"
#include "Loader.h"
#include "Greedy.h"
#include "Generator.h"

using namespace std;

int main()
{
//	new Generator();
	
	clock_t start, stop;
	vector<string> data = Loader::readFromFile();
	GraphClass::vertex = data.size();
    Graph.create();
	Graph.calculateWeight(data);

//	Graph.print();
//	Loader::showTime(start, stop);

//	Greedy greedy;
//	greedy.start(0, 0);
//	greedy.printResult();

	GeneticClass Genetic;
    Genetic.Interface();

	cin.get(); 
    return 0;
}


