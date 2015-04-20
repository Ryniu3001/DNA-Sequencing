#include <iostream>
#include <stdlib.h>
#include "graf.hpp"
#include "alg.hpp"

using namespace std;
int main()
{
    cout << "Podaj liczbe wierzcholkow: ";
    cin >> GraphClass::vertex;
    cout << "Podaj max wage: ";
    cin >> GraphClass::maxWeight;
    cout << endl;

    Graph.create();
    Graph.print();
    cout << endl;

/////////////////  GENETIC ///////////////////
    GeneticClass Genetic;
    Genetic.Interface();
    return 0;
}
