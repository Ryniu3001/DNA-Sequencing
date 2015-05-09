#include "alg.hpp"

// DO USUNIÊCIA  
void GeneticClass::checkOthers(){
	for (int i = 0; i < lc; i++){
		// tworzony wektor odzwiedzonych wypelniony false
		vector <bool> visited(GraphClass::vertex);


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
					if ((j < GraphClass::vertex) && (!visited[nastepniki[poprzednik][pos][0]]))			//wybierz pierwszego nastepnika z listy i sprawdz czy byl juz odwiedzony
					{
						chromosom[i][j] = nastepniki[poprzednik][pos][0];
						visited[chromosom[i][j]] = true;
						found = true;
						break;
					}
					else
					{
						int v = rand() % siz;
						if ((!visited[nastepniki[poprzednik][v][0]]))
						{
							chromosom[i][j] = nastepniki[poprzednik][pos][0];
							visited[chromosom[i][j]] = true;
							found = true;
							break;
						}
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
				//printf("Wierzcholek %d nie ma nastepnikow !!??!!?? %d %d\n", chromosom[i][j - 1], i, j - 1);
			}
		}
	}
}
void listaOdniesienia(){
	/*
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



	/*  for (int i=0;i<lc;i++){      // Wypisywanie chromosomow (zakodowanych)
	cout << endl;
	for (int j=0; j<GraphClass::vertex; j++)
	cout << chromosom[i][j]<< " ";
	}
	cout << endl;
	*/
}

list<int> GeneticClass::createList(vector<int> chromosome){
	list<int> lista;
	for (int i = 0; i<GraphClass::vertex; i++){
		lista.push_back(i);
	}
	return lista;
}

void GeneticClass::printList(list<int> lista){
	for (list<int>::iterator iter = lista.begin(); iter != lista.end(); iter++)
		cout << *iter << " ";
	cout << endl;
}

int GeneticClass::removeFromList(int a, list<int> lista){
	int value = 0;
	if (lista.size() > 0){
		list<int>::iterator iter = lista.begin();
		for (int i = 0; i < a - 1; i++){
			iter++;
		}
		value = *iter;
		lista.erase(iter);
	}
	return value;
}

void showVector(vector<int> wektor){
	for (int i = 0; i < wektor.size(); i++)
		cout << wektor[i] << "  ";
	cout << endl;
}

bool rosnaco(vector<int> const a, vector<int> const b)
{
	return a[1] < b[1];
}

void GeneticClass::initializeVectors(){
	bestScoreInAll = 0;

	path.clear();
	ratings.clear();
	chromosom.clear();
	children.clear();
	
	for (int i = 0; i < GraphClass::vertex; i++)
		path.push_back(0);

	for (int i = 0; i < lc; i++)
		ratings.push_back(0);

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

void GeneticClass::generateNastepniki(){
	// Tworzenie wektora wierzcholkow, kazdy wierzcholek ma wektor wierzcholkow ktore pasuja do niego i maja ocene mniejsza od 1000
	nastepniki.resize(GraphClass::vertex);
	for (int i = 0; i <GraphClass::vertex; i++)		{
		for (int j = 0; j < GraphClass::vertex; j++)
		{
			if (GraphClass::matrix[i][j] != 1000){
				vector<int> para(2);
				para[0] = j;
				para[1] = GraphClass::matrix[i][j];
				nastepniki[i].push_back(para);
			}
		}
		sort(nastepniki[i].begin(), nastepniki[i].end(), rosnaco);
		// cout << i << ":\t";		showVector(nastepniki[i]);
	}
}

void GeneticClass::createChromosom(int j, vector <bool> &visited, vector<int> &chrom, int dnaLen, bool random)
{
	while (j < GraphClass::vertex)
	{
		int siz = nastepniki[chrom[j - 1]].size();				// liczba pasujacych nastepnikow
		int poprzednik = chrom[j - 1];
		if ((siz) && (!visited[nastepniki[poprzednik][0][0]]) && (dnaLen < Loader::optimum) && (!random))
		{
			chrom[j] = nastepniki[poprzednik][0][0];
			dnaLen += nastepniki[poprzednik][0][1];
			visited[chrom[j]] = true;
		}
		else if ((siz) && (dnaLen < Loader::optimum)) //Jesli najlepszy bedzie zajety to bierzemy nastepny nieodwiedzony z listy nastepnikow 
		{
			int pos;
			for (pos = 0; pos < siz; pos++)
			{
				int pozycja = rand() % siz;
				if ((!visited[nastepniki[poprzednik][pozycja][0]]))
				{
					chrom[j] = nastepniki[poprzednik][pozycja][0];
					dnaLen += nastepniki[poprzednik][pozycja][1];
					visited[chrom[j]] = true;
					break;
				}
			}
			if (pos == siz)				//nie udalo sie wybrac nastepnika wiec przerywamy
			{
				chrom.resize(j);
				break;
			}
		}
		else
		{
			chrom.resize(j);
			break;
		}
		j++;
	}
}

void GeneticClass::DrawingPopulation(){
	srand(time(NULL));
	initializeVectors();
	generateNastepniki();
		
	for (int i = 0; i < lc; i++){
		vector <bool> visited(GraphClass::vertex);
		for (int g = 0; g<visited.size(); g++)
			visited[g] = false;												
		chromosom[i][0] = i % GraphClass::vertex;							//poczatkowy wierzcholek
		visited[chromosom[i][0]] = true;
		unsigned int dnaLen = 10;											//TODO: zmienic 10 na jakas zmienna czy cos
		int j = 1;

		createChromosom(j, visited, chromosom[i], dnaLen, !(i < GraphClass::vertex));
	}
}	//TODO: przypadek dla 2 mozliwosci wyboru w przesuniêciu o 1

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

void GeneticClass::Crossover(int parent1, int parent2, vector<int> &child1, vector<int> &child2){



	for (int i = 0; i <= (GraphClass::vertex / 2); i++){
		child1[i] = chromosom[parent1][i];
		child2[i] = chromosom[parent2][i];
	}

	for (int i = (GraphClass::vertex / 2) + 1; i<GraphClass::vertex; i++){
		child1[i] = chromosom[parent2][i];
		child2[i] = chromosom[parent1][i];
	}
}	
//	TODO: krzy¿owanie przy przesuniêciu powy¿ej 1

int getWorst(vector<int> chromosome){
	int worst = 0, score = -1;
	
	for (int i = 1; i < chromosome.size(); i++)
		if (score < GraphClass::matrix[chromosome[i-1]][chromosome[i]]){
			score = GraphClass::matrix[chromosome[i - 1]][chromosome[i]];
			worst = i;
		}

	return worst;
}

void GeneticClass::Mutation(vector<int> &chromosome){


	int index1 = -1;
	int index2 = -1;
	int node = -1;
	for (int i = 0; i < (chromosome.size() - 1); i++){
		int current = chromosome[i];
		int next = chromosome[i + 1]; 
		int size = nastepniki[current].size() - 1;

		for (int j = 0; j < size; j++){
			if (nastepniki[current][j][0] == next){
				if (nastepniki[current][j][1] == nastepniki[current][j+1][1]){
					node = nastepniki[current][j + 1][0];
					break;
				}
			}
		}

		if (node > 0){
			index1 = i+1;
			for (int j = 0; j < chromosome.size(); j++){
				if (chromosome[j] == node){
					index2 = j;
					break;
				}
			}
			break;
		}
	}

	if (index2 > 0){
		chromosome[index1] = chromosome[index2];
	}
	else {
		chromosome[index1] = node;
	}

	vector<bool> visited(GraphClass::vertex);
	int rate = 10;
	visited[chromosome[0]] = true;
	for (int i = 0; i < index1; i++){
		int current = chromosome[i];
		int next = chromosome[i + 1];
		rate += GraphClass::matrix[current][next];
		visited[next] = true;
	}
	createChromosom(index1+1, visited, chromosome, rate, false);


/*	for (int i = 0; i < chromosome.size(); i++)
		cout << chromosome[i] << "  ";
	cout << endl; 
*/
}
// TODO: mutacja zamienia w vektorze 2 elementy czy ma mozliwosc dodania nowego wyrazu lub zamiany na nowy w konfiguracji
// TODO: zamienia przy 2 równie dobrych nastêpnikach

int GeneticClass::Rating()
{
	int bestRating = -1, bestChromosom = -1;
	vector<int> chromosomBestPath;
	fill(ratings.begin(), ratings.end(), 0);
	for (int i = 0; i<lc; i++){
		vector<int> tmpPath(GraphClass::vertex);
		ratings[i] = chromosom[i].size();				

		if ((ratings[i] > bestRating) || (bestRating == -1))
		{
			bestRating = ratings[i];
			bestChromosom = i;
		}
	}

	if ((bestScoreInAll > bestRating) || (bestScoreInAll == 0))
	{
		path = chromosom[bestChromosom];
		bestScoreInAll = bestRating;
	}
	return bestRating;
}

void GeneticClass::showBest(){
	cout << "\nGenetic best score: " << bestScoreInAll << endl << endl;
	printBest();
}

void GeneticClass::printBest(){
	int dnaLength = 0;
	for (int i = 0; i<path.size(); i++){
		if (i > 0)
		{
			cout << " <" << GraphClass::matrix[path[i - 1]][path[i]] << "> " << path[i];
			dnaLength += GraphClass::matrix[path[i - 1]][path[i]];
		}
		else
		{
			cout << path[i];
		}
	}

	cout << endl << "Dlugosc DNA: " << dnaLength+10 ;		//TODO: Tak samo jak przy generowaniu populacji cos z ta 10 trzeba zrobic.
}


void GeneticClass::checksRepeatsInChromosom(){
	cout << "SPRAWDZAMY POWTORZENIA IN CHROMOSOM ... ";
	for (int i = 0; i < lc; i++){
		for (int j = i + 1; j < lc; j++){
			bool noRepeat = false;
			for (int k = 0; k < GraphClass::vertex; k++){
				if (chromosom[i][k] != chromosom[j][k]){
					noRepeat = true;
					break;
				}
			}
			if (!noRepeat)
				cout << endl << "Chromosomy takie same to: " << i << " oraz " << j << endl;
		}
	}
	cout << "KONIEC" << endl;
}

void GeneticClass::checksRepeatsInSet(){
	cout << "SPRAWDZAMY POWTORZENIA IN SET ... ";
	for (int i = 0; i < lc; i++){
		vector<bool> visited(GraphClass::vertex);
		for (int j = 0; j < GraphClass::vertex; j++){
			if (!visited[chromosom[i][j]])
				visited[chromosom[i][j]] = true;
			else
				cout << endl << "W CHROMOSOMIE " << i << " POWTORZENIA" << endl;
		}
	}
	cout << "KONIEC" << endl << endl;
}

///////////////////////////////  INTERFACE  ////////////////////////////////
void GeneticClass::Interface(){
	lc = 3000;                        

	int algorithmIteration = 1;
	int score = 0, parent1, parent2;

	DrawingPopulation();
	Rating();
	cout << "Rodzice: " << bestScoreInAll << endl;

/*	////////////// SELEKCJA I KRZYZOWANIE I MUTACJA///////////////////////////////
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
			int target = TournamentSelection(10);
			Mutation(chromosom[target]);//chromosom[target]);				//		przy zakomentowanym krzyzowaniu wpisalem tu chromosom zamiast children //
		}

		//chromosom.swap(children);						//zakomentowany swap bo zakomentowane krzyzowanie // 	
		score = Rating();
		cout << "Populacja_" << z << "  = " << score << endl;
	}
*/
//	Mutation(path);
	showBest();
}

GeneticClass::~GeneticClass(){
}