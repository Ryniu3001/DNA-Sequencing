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
	Loader::getFileNames();

	for (int i = 0; i < Loader::fileNames.size(); i++){
		vector<string> data = Loader::readFromFile(Loader::fileNames[i]);
		GraphClass::vertex = data.size();
		Graph.create();
		Graph.calculateWeight(data);

		GeneticClass Genetic;
		Genetic.Interface();
		//Loader::showTime(start, stop);
	}
	cin.get(); 
    return 0;
}


