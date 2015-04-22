#include <iostream>
#include <stdlib.h>
#include "graf.hpp"
#include "alg.hpp"
#include "Loader.h"

using namespace std;
vector<string> Loader::data = initializer_list<string>();


int main()
{
	Loader::readFromFile();
	//Loader::show();			odwolujesz siê Loader::data[i] i musisz miec #include "Loader.h"

    cout << "Podaj liczbe wierzcholkow: ";
    cin >> GraphClass::vertex;
    cout << "Podaj max wage: ";
    cin >> GraphClass::maxWeight;
    cout << endl;

    Graph.create();
    //Graph.print();
    cout << endl;

/////////////////  GENETIC ///////////////////
    GeneticClass Genetic;
    Genetic.Interface();
    return 0;
}


