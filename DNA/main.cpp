#include "graf.hpp"
#include "alg.hpp"
#include "Loader.h"
#include "Greedy.h"
#include "Generator.h"
#include "Saver.h"

using namespace std;

int main()
{
	//new Generator();

	Loader::getFileNames();

	for (int i = 0; i < Loader::fileNames.size(); i++){
		vector<string> data = Loader::readFromFile(Loader::fileNames[i]);
		GraphClass::vertex = data.size();
		Saver *saver = new Saver(Loader::fileNames[i]);
				
		Graph.create();
		Graph.calculateWeight(data);

		GeneticClass Genetic;
		Genetic.Interface();

		saver->write();
	}

	Saver::rate();

	cin.get(); 
    return 0;
}


