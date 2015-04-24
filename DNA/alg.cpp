#include "alg.hpp"
#include <algorithm>

void GeneticClass::CreateList(){
	for (int i = 0; i<GraphClass::vertex; i++){
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


void GeneticClass::showVector(vector< vector<int> > wektor){
	for (int i = 0; i < wektor.size(); i++)
		cout << wektor[i][0] << "  ";
	cout << endl;
}

bool rosnaco(vector<int> const a, vector<int> const b)
{
	return a[1] < b[1];
}

void GeneticClass::initializeVectors(){
	for (int i = 0; i < GraphClass::vertex; i++)
		path.push_back(0);											// Kolejnosc miast w najelpszym rozwiazaniu

	for (int i = 0; i < lc; i++)
		ratings.push_back(0); // vector do przechowywania ocen kazdego osobnika

	for (int i = 0; i < lc; i++){
		vector<int> row1;
		vector<int> row2;
		for (int j = 0; j < GraphClass::vertex; j++){
			row1.push_back(0);
			row2.push_back(0);
		}
		children.push_back(row1);
		chromosom.push_back(row2);
	}
}

void GeneticClass::DrawingPopulation(){
	srand(time(NULL));
	/*  for (int i=0; i<lc; i++)
	for (int j=0; j<GraphClass::vertex; j++)
	chromosom[i][j] = rand() % (GraphClass::vertex-j); // Kodowanie chromosomow z lista odniesienia
	*/


	/////////////////START: NIEOPTYMALNY KOD DO PRZETESTOWANIA WYNIKU ////////////////////////

	// Tworzenie wektora wierzcholkow, kazdy wierzcholek ma wektor wierzcholkow ktore pasuja do niego i maja ocene mniejsza od 1000
	vector< vector < vector<int> > > nastepniki(GraphClass::vertex);
	for (int i = 0; i <GraphClass::vertex; i++)		{
		for (int j = 0; j < GraphClass::vertex; j++)	{
			if (GraphClass::matrix[i][j] != 1000){
				vector<int> para(2);
				para[0] = j;
				para[1] = GraphClass::matrix[i][j];
				nastepniki[i].push_back(para);
			}
		}
		sort(nastepniki[i].begin(), nastepniki[i].end(), rosnaco);
		//		cout << i << ":\t";		showVector(nastepniki[i]);
	}
	// TODO - posortowaæ

	for (int i = 0; i < lc; i++){
		// tworzony wektor odzwiedzonych wypelniony false
		vector <bool> visited(GraphClass::vertex);
		for (int g = 0; g<visited.size(); g++)
			visited[g] = false;

		// wypelnianie pierwszego wierzcholka w chromosomie losowo
		chromosom[i][0] = rand() % GraphClass::vertex;
		visited[chromosom[i][0]] = true;

		// tworzenie danego chromosomu
		for (int j = 1; j < GraphClass::vertex; j++)
		{
			bool found = false;
			int siz = nastepniki[chromosom[i][j - 1]].size();				// liczba pasujacych nastepnikow
			if (siz != 0)
			{
				int poprzednik = chromosom[i][j - 1];			// ? int poprzednik = chromosom.at(i).at(j - 1);
				for (int pos = 0; pos < siz; pos++)
				{
					if (!visited[nastepniki[poprzednik][pos][0]])			//wybierz pierwszego nastepnika z listy i sprawdz czy byl juz odwiedzony
					{
						chromosom[i][j] = nastepniki[poprzednik][pos][0];
						visited[chromosom[i][j]] = true;
						found = true;
						break;
					}
				}
				if (!found)		//jeœli wszystkie na liscie nastepniko byly juz wczesniej odwiedzone dobierz losowo nieodwiedzony wierzcholek
				{
					//printf("Nie dopasowano nastepnika ?! %d %d %d \n", i, j, chromosom[i][j - 1]);
					//chromosom[i][j] = rand() % GraphClass::vertex;
					for (int l = 0; l < GraphClass::vertex; l++)
					if (!visited[l])
					{
						visited[l] = true;
						chromosom[i][j] = l;
						break;
					}
				}
			}
			else		// jeœli brak pasuj¹cych nastêpników, bierz losowo
			{
				for (int l = 0; l < GraphClass::vertex; l++)
				if (!visited[l])
				{
					visited[l] = true;
					chromosom[i][j] = l;
					break;
				}
				printf("Wierzcholek %d nie ma nastepnikow !!??!!?? %d %d\n", chromosom[i][j - 1], i, j - 1);
			}
		}
	}

	// lista odniesienia
	list<int> listaOdn(GraphClass::vertex);
	list<int>::iterator iter;
	for (int i = 0; i < lc; i++)
	{
		listaOdn.clear();
		for (int ii = 0; ii < GraphClass::vertex; ii++)
			listaOdn.push_back(ii);

		for (int j = 0; j < GraphClass::vertex; j++)
		{
			int result = 0;
			int chrom = chromosom[i][j];
			for (iter = listaOdn.begin(); iter != listaOdn.end(); iter++)
			if (*iter == chrom)
				break;
			else
				result++;

			chromosom[i][j] = result;
			listaOdn.erase(iter);
		}
	}
	/////////////////STOP: NIEOPTYMALNY KOD DO PRZETESTOWANIA WYNIKU ////////////////////////


	/*  for (int i=0;i<lc;i++){      // Wypisywanie chromosomow (zakodowanych)
	cout << endl;
	for (int j=0; j<GraphClass::vertex; j++)
	cout << chromosom[i][j]<< " ";
	}
	cout << endl;
	*/
} 

int GeneticClass::TournamentSelection(int x){
	int best = (rand()*rand()) % lc;
	int found;
	for (int i = 0; i<x; i++){
		found = (rand()*rand()) % lc;
		if (ratings[found] < ratings[best])
			best = found;
	}
	return best;
}

void GeneticClass::Crossover(int par1, int par2, vector<int> &child1, vector<int> &child2){
	for (int i = 0; i <= (GraphClass::vertex / 2); i++){
		child1[i] = chromosom[par1][i];
		child2[i] = chromosom[par2][i];
	}

	for (int i = (GraphClass::vertex / 2) + 1; i<GraphClass::vertex; i++){
		child1[i] = chromosom[par2][i];
		child2[i] = chromosom[par1][i];
	}
}

void GeneticClass::Mutation(vector<int> &chromosome){
	short int target;
	target = rand() % GraphClass::vertex;

	for (int i = 0; i < chromosome.size(); i++)
		cout << chromosome[i] << "  ";
	cout << endl;

	chromosome[target] = rand() % (GraphClass::vertex - target);

	for (int i = 0; i < chromosome.size(); i++)
		cout << chromosome[i] << "  ";
	cout << endl;
}

int GeneticClass::Rating()
{
	int bestRating = 0;
	int sum, from, to, startFrom;

	for (int i = 0; i<lc; i++){
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

		if ((bestRating > sum) || (bestRating == 0)){ // Zapamietuje najlepszy wynik (ocene)
			bestRating = sum;
			bestChromosom = i;
		}
	}
	for (int i=0;i<lc;i++) // Wypisanie ocen populacji
	//	    cout << ratings[i] << endl;

	if (bestScoreInAll > bestRating){
		bestScoreInAll = bestRating;
		bestChromosomInAll = bestChromosom;
	}

	return bestRating;
}

void GeneticClass::showBest(){
	cout << "\nGenetic best score: " << bestScoreInAll << "\n";
	CreateList();
	for (int i = 0; i<GraphClass::vertex; i++){
		path[i] = removeFromList(chromosom[bestChromosomInAll][i]);
		if (i > 0)
			cout << " <" << GraphClass::matrix[path[i - 1]][path[i]] << "> " << path[i];
		else
			cout << path[i];
	}
}



///////////////////////////////  INTERFACE  ////////////////////////////////
void GeneticClass::Interface(){
	lc = 1000;                        
	bestScoreInAll = 0;
	bestChromosom = -1;
	int algorithmIteration = 5;
	int score = 0, parent1, parent2;

	initializeVectors();
	DrawingPopulation();
	bestScoreInAll = Rating();
	cout << "Rodzice: " << bestScoreInAll << endl;

	////////////// SELEKCJA I KRZYZOWANIE I MUTACJA///////////////////////////////
	for (int z = 0; z<algorithmIteration; z++){
		int P = -1;		                            // licznik nowej populacji
		while (P < lc - 2){
			parent1 = TournamentSelection(10);
			do
				parent2 = TournamentSelection(10);
			while (parent1 == parent2);
			Crossover(parent1, parent2, children[P+1], children[P+2]);
			P += 2;
		}

		int mutationIteration = P / 2;
		for (int i = 0; i<mutationIteration; i++){
			int target2 = (rand()*rand()) % lc;
			Mutation(children[target2]);
		}

		chromosom.swap(children);					
		score = Rating();
		cout << "Populacja " << z << " " << score << endl;
	}
	showBest();
}

GeneticClass::~GeneticClass(){
}