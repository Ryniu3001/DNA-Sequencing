#include "graf.hpp"
#include "alg.hpp"
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;

void GeneticClass::DrawingPopulation(int liczbaChromosomow){
    chromosom = (short int**) calloc (liczbaChromosomow,sizeof(short int*)); // tablica chromosomow
    for (int i=0; i<liczbaChromosomow; i++)
       chromosom[i] = (short int*) calloc (GraphClass::vertex,sizeof(short int));

    srand(time(NULL));
    for (int i=0; i<liczbaChromosomow; i++)
        for (int j=0; j<GraphClass::vertex; j++)
            chromosom[i][j] = rand() % (GraphClass::vertex-j); // Kodowanie chromosomow z lista odniesienia

    ratings = (int*) calloc (liczbaChromosomow,sizeof(int)); // tablica do przechowywania ocen kazdego osobnika


//    for (int i=0;i<liczbaChromosomow;i++){      // Wypisywanie chromosomow (zakodowanych)
//    cout << endl;                               //
//    for (int j=0; j<GraphClass::vertex; j++)          //
//        cout << chromosom[i][j];        //
//    }                                           //
//    cout << endl;                               //

}

//Lista odniesienia
void GeneticClass::CreateList(){
    head = (ListStruct*) calloc (1,sizeof(ListStruct));
    head->value = 0;
    ListStruct *tmp;
    tmp = head;

    for (int i=1; i<GraphClass::vertex; i++){
        tmp->next = (ListStruct*) calloc (1,sizeof(ListStruct));
        tmp = tmp->next;
        tmp->value = i;
    }
}

void GeneticClass::PrintList(){
    cout << endl;
    ListStruct *tmp;
    tmp = head;
    while (tmp != NULL){
        cout << tmp->value << " ";
        tmp = tmp->next;
    }
    cout << endl;
}

int GeneticClass::removeFromList(int a){
    int b;
    ListStruct *tmp;
    ListStruct *beforeTmp = 0;
    tmp = head;

    if (a==0){
        b = head->value;
        tmp=head->next;
        free(head);
        head = tmp;
    }
    else{
        for (int i=0; i<a; i++){
            beforeTmp = tmp;
            tmp = tmp->next;
        }
        b = tmp->value;
        beforeTmp->next = tmp->next;
        free(tmp);
    }
return b;
}

//Zwraca najelepszy czas drogi.
int GeneticClass::Rating(int liczbaChromosomow, int *bestChromosom)
{
    int bestRating=0;
    int sum,from,to,startFrom;
    for (int i=0; i<liczbaChromosomow;i++){
        sum = 0;
        CreateList();
        from = removeFromList(chromosom[i][0]); //Poczatek drogi (pierwszy wierzcholek)
        startFrom = from;
        for (int j=1; j<GraphClass::vertex; j++){
            to = removeFromList(chromosom[i][j]);
            sum += GraphClass::matrix[from][to];
            from = to;
        }
        sum += GraphClass::matrix[to][startFrom];
        ratings[i] = sum;
        if ((bestRating > sum) || (bestRating == 0)){ // Zapamietuje najlepszy wynik (ocene)
            bestRating = sum;
            *bestChromosom = i;
        }
    }
//    for (int i=0;i<liczbaChromosomow;i++) // Wypisanie ocen populacji
//        cout << ratings[i] << endl;
return bestRating;
}

int GeneticClass::TournamentSelection(int x,int liczbaChromosomow){
    int best = (rand()*rand()) % liczbaChromosomow;
    int found;
    for (int i=0; i<x; i++){
        found = (rand()*rand()) % liczbaChromosomow;
        if (ratings[found] < ratings[best])
            best = found;
    }
return best;
}

void GeneticClass::Crossover(int par1, int par2, short int child1[], short int child2[]){
    for (int i=0; i<=(GraphClass::vertex/2);i++){
        child1[i] = chromosom[par1][i];
        child2[i] = chromosom[par2][i];
    }

    for (int i=(GraphClass::vertex/2)+1; i<GraphClass::vertex ;i++){
        child1[i] = chromosom[par2][i];
        child2[i] = chromosom[par1][i];
    }
}

void GeneticClass::Mutation(short int chromosome[]){
    short int target;
    target = rand() % GraphClass::vertex;
    chromosome[target] = rand() % (GraphClass::vertex - target);
}

////////////////////////////////////////////////////////////////////////////
///////////////////////////////  INTERFACE  ////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void GeneticClass::Interface(){

    int P,M,score=0,k=0;                // P - licznik nowej populacji, M-ilosc mutacji, score - najlepszy czas przebycia drogi w danej populacji
    short int **tmp;
    lc = 70000;                                                        // populacja
    short int *path;
    int p=-1;
    path = (short int*) calloc (GraphClass::vertex,sizeof(short int)); // Kolejnosc miast w najelpszym rozwiazaniu
    children = (short int**) calloc (lc,sizeof(short int*));
    for (int i=0; i<lc; i++)
       children[i] = (short int*) calloc (GraphClass::vertex,sizeof(short int));

    DrawingPopulation(lc);
    int parent1,parent2;

    score = Rating(lc,&p);
    bestScoreInAll = score;
    bestChromosomInAll = p;

    cout << "\nRodzice: " << score;                    // Ocena rodzicow

////////////// SELEKCJA I KRZYZOWANIE ///////////////////////////////
   for (int z=0; z<15; z++){
   // while (1){
    //if(kbhit()) break; // Przerwanie przy wcisnieciu klawisza
        P=-1;
        while (P < lc-2){
            parent1 = TournamentSelection(5,lc);
            do
                parent2 = TournamentSelection(5,lc);
            while (parent1 == parent2);
            Crossover(parent1,parent2,children[++P],children[++P]);
        }

///////////// MUTACJA  /////////////////////////////////////////
        M=P/5;
        for (int i=0; i<M; i++){
            int target2 = (rand()*rand()) % lc;
            Mutation(children[target2]);
        }
///////////////////////////////////////////////////////////////
        tmp = chromosom;
        chromosom = children;
        children = tmp;

        score = Rating(lc,&p);
        if (bestScoreInAll > score ){
            bestScoreInAll = score;
            bestChromosomInAll = p;
        }

        cout << "\nPopulacja " << k++ << " " << score;
    }
////////// WYNIK ///////////////////////////////////////////////
    cout << "\nGenetic best score: " << bestScoreInAll << "\n";
    CreateList();
    for (int i=0; i<GraphClass::vertex; i++){
        path[i] = removeFromList(chromosom[bestChromosomInAll][i]);
        cout << path[i] << " ";
    }

  cin.sync(); //kasowanie zbędnych znaków z bufora
  cin.get(); //oczekiwanie na wciśnięcie klawisza
}

GeneticClass::~GeneticClass(){
    if (chromosom != NULL)
        for (int i=0; i<lc;i++)
            free(chromosom[i]);
    if (children != NULL)
        for (int i=0; i<lc;i++)
            free(children[i]);

    free(chromosom);
    free(children);
}
