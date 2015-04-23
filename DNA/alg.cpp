#include "alg.hpp"

void GeneticClass::DrawingPopulation(int liczbaChromosomow){
	for (int i = 0; i < liczbaChromosomow; i++){
		vector<int> row;
		for (int j = 0; j < GraphClass::vertex; j++)
			row.push_back(0);
		chromosom.push_back(row);
	}

	srand(time(NULL));
	/*   for (int i=0; i<liczbaChromosomow; i++)
	for (int j=0; j<GraphClass::vertex; j++)
	chromosom[i][j] = rand() % (GraphClass::vertex-j);*/ // Kodowanie chromosomow z lista odniesienia


	/////////////////START: NIEOPTYMALNY KOD DO PRZETESTOWANIA WYNIKU ////////////////////////

	vector< vector <int> > tmp(GraphClass::vertex);

	for (int i = 0; i <GraphClass::vertex; i++)
	{
		for (int j = 0; j < GraphClass::vertex; j++)
		{
			if (GraphClass::matrix[i][j] != 1000)
				tmp[i].push_back(j);
		}
	}

	for (int i = 0; i < liczbaChromosomow; i++)
	{
		chromosom[i][0] = rand() % GraphClass::vertex;
		for (int j = 1; j < GraphClass::vertex; j++)
		{
			int siz = tmp[chromosom[i][j - 1]].size();
			if (siz != 0)
			{
				int pos = rand() % siz;
				chromosom[i][j] = tmp[chromosom[i][j - 1]][pos];
			}
			else
			{
				chromosom[i][j] = rand() % GraphClass::vertex;
				//printf("Wierzcholek %d nie ma nastepnikow !!??!!?? %d %d\n", chromosom[i][j - 1], i, j - 1);
			}
		}
	}


	list<int> listaOdn(GraphClass::vertex);
	list<int>::iterator pos;

	for (int i = 0; i < liczbaChromosomow; i++)
	{
		listaOdn.clear();
		for (int i = 0; i < GraphClass::vertex; i++)
			listaOdn.push_back(i);
		int max = GraphClass::vertex - 1;
		for (int j = 1; j < GraphClass::vertex; j++)
		{
			pos = find(listaOdn.begin(), listaOdn.end(), chromosom[i][j]);
			if (*pos < max)
				chromosom[i][j] = *pos;
			else
				chromosom[i][j] = rand() % max;
			max -= 1;
		}
	}
	/////////////////STOP: NIEOPTYMALNY KOD DO PRZETESTOWANIA WYNIKU ////////////////////////

	for (int i = 0; i < liczbaChromosomow; i++)
		ratings.push_back(0); // vector do przechowywania ocen kazdego osobnika


	//    for (int i=0;i<liczbaChromosomow;i++){      // Wypisywanie chromosomow (zakodowanych)
	//    cout << endl;                               //
	//    for (int j=0; j<GraphClass::vertex; j++)          //
	//        cout << chromosom[i][j];        //
	//    }                                           //
	//    cout << endl;                               //

}

//Lista odniesienia
void GeneticClass::CreateList(){
	for (int i = 1; i<GraphClass::vertex; i++){
		head.push_back(i);
	}
}

void GeneticClass::PrintList(){
	for (list<int>::iterator iter = head.begin(); iter != head.end(); iter++)
		cout << *iter << " ";
	cout << endl;
}

int GeneticClass::removeFromList(int a){
	int value = 0;
	a = 0;
	if (head.size() > 0){
		list<int>::iterator iter = head.begin();
		for (int i = 0; i < a - 1; i++){
			iter++;
		}
		value = *iter;
		head.erase(iter);
	}
	return value;
}

//Zwraca najelepszy czas drogi.
int GeneticClass::Rating(int liczbaChromosomow, int *bestChromosom)
{
	int bestRating = 0;
	int sum, from, to, startFrom;
	for (int i = 0; i<liczbaChromosomow; i++){
		sum = 0;
		CreateList();
		from = removeFromList(chromosom[i][0]); //Poczatek drogi (pierwszy wierzcholek)
		startFrom = from;
		for (int j = 1; j<GraphClass::vertex; j++){
			to = removeFromList(chromosom[i][j]);
			sum += GraphClass::matrix[from][to];
			from = to;
		}
		sum += GraphClass::matrix[to][startFrom];
		ratings[i] = sum;
		if (sum > 100000)
			sum += 500000;
		if ((bestRating > sum) || (bestRating == 0)){ // Zapamietuje najlepszy wynik (ocene)
			bestRating = sum;
			*bestChromosom = i;
		}
	}
	//for (int i=0;i<liczbaChromosomow;i++) // Wypisanie ocen populacji
	//    cout << ratings[i] << endl;
	return bestRating;
}

int GeneticClass::TournamentSelection(int x, int liczbaChromosomow){
	int best = (rand()*rand()) % liczbaChromosomow;
	int found;
	for (int i = 0; i<x; i++){
		found = (rand()*rand()) % liczbaChromosomow;
		if (ratings[found] < ratings[best])
			best = found;
	}
	return best;
}

void GeneticClass::Crossover(int par1, int par2, vector<int> child1, vector<int> child2){
	for (int i = 0; i <= (GraphClass::vertex / 2); i++){
		child1[i] = chromosom[par1][i];
		child2[i] = chromosom[par2][i];
	}

	for (int i = (GraphClass::vertex / 2) + 1; i<GraphClass::vertex; i++){
		child1[i] = chromosom[par2][i];
		child2[i] = chromosom[par1][i];
	}
}

void GeneticClass::Mutation(vector<int> chromosome){
	short int target;
	target = rand() % GraphClass::vertex;
	chromosome[target] = rand() % (GraphClass::vertex - target);
}

////////////////////////////////////////////////////////////////////////////
///////////////////////////////  INTERFACE  ////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void GeneticClass::Interface(){

	int P, M, score = 0, k = 0, p = -1;;                // P - licznik nowej populacji, M-ilosc mutacji, score - najlepszy czas przebycia drogi w danej populacji
	lc = 1000;                                          // populacja
	vector<int> path;
	vector<vector<int>> tmp;
	for (int i = 0; i < GraphClass::vertex; i++)
		path.push_back(0);											// Kolejnosc miast w najelpszym rozwiazaniu
	for (int i = 0; i < lc; i++){
		vector<int> row;
		for (int j = 0; j < GraphClass::vertex; j++)
			row.push_back(0);
		children.push_back(row);
	}

	DrawingPopulation(lc);
	int parent1, parent2;

	score = Rating(lc, &p);
	bestScoreInAll = score;
	bestChromosomInAll = p;

	cout << "\nRodzice: " << score;                    // Ocena rodzicow

	////////////// SELEKCJA I KRZYZOWANIE ///////////////////////////////
	for (int z = 0; z<50; z++){
		// while (1){
		//if(kbhit()) break; // Przerwanie przy wcisnieciu klawisza
		P = -1;
		while (P < lc - 2){
			parent1 = TournamentSelection(10, lc);
			do
			parent2 = TournamentSelection(10, lc);
			while (parent1 == parent2);
			Crossover(parent1, parent2, children[++P], children[++P]);
		}

		///////////// MUTACJA  /////////////////////////////////////////
		M = P / 2;
		for (int i = 0; i<M; i++){
			int target2 = (rand()*rand()) % lc;
			Mutation(children[target2]);
		}
		///////////////////////////////////////////////////////////////
		tmp = chromosom;
		chromosom = children;
		children = tmp;

		score = Rating(lc, &p);
		if (bestScoreInAll > score){
			bestScoreInAll = score;
			bestChromosomInAll = p;
		}

		cout << "\nPopulacja " << k++ << " " << score;
	}
	////////// WYNIK ///////////////////////////////////////////////
	cout << "\nGenetic best score: " << bestScoreInAll << "\n";
	CreateList();
	for (int i = 0; i<GraphClass::vertex; i++){
		path[i] = removeFromList(chromosom[bestChromosomInAll][i]);
		cout << path[i] << " ";
	}

	cin.sync(); //kasowanie zbędnych znaków z bufora
	cin.get(); //oczekiwanie na wciśnięcie klawisza
}

GeneticClass::~GeneticClass(){
}