#include "graf.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int GraphClass::vertex;
int GraphClass::maxWeight;
int **GraphClass::matrix;

GraphClass Graph;
void GraphClass::create(){
//Alokacja pamieci
    matrix = (int**) calloc (vertex,sizeof(int*));
    for (int i=0;i<vertex;i++)
        matrix[i] = (int*) calloc (vertex, sizeof(int));
//Losowanie wag
    srand(time(NULL));
    for (int i=0; i<vertex; i++)
        for (int j=i+1; j<vertex; j++){
            matrix[i][j] = 1 + rand() % maxWeight;
            matrix[j][i] = matrix[i][j];
        }
};

void GraphClass::print(){
    for (int i=0; i<vertex; i++){
        cout << endl;
        for (int j=0; j<vertex; j++)
            cout << matrix[i][j] << " ";
    }

};

GraphClass::~GraphClass(){
    for (int i=0;i<vertex;i++)
        free(matrix[i]);
    free(matrix);
}
