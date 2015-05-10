#include "alg.hpp"

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
		if (dnaLen > Loader::optimum)
		{
			chrom.resize(j - 1);
			break;
		}
		int siz = nastepniki[chrom[j - 1]].size();				// liczba pasujacych nastepnikow
		int poprzednik = chrom[j - 1];
		if ((siz) && (!visited[nastepniki[poprzednik][0][0]]) && (!random))
		{
			chrom[j] = nastepniki[poprzednik][0][0];
			dnaLen += nastepniki[poprzednik][0][1];
			visited[chrom[j]] = true;
		}
		else if ((siz)) //Jesli najlepszy bedzie zajety to bierzemy nastepny nieodwiedzony z listy nastepnikow 
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

		createChromosom(j, visited, chromosom[i], dnaLen, true);			//losowo - true, deterministycznie - !(i < GraphClass::vertex)
	}
}	

int GeneticClass::TournamentSelection(int x){
	int best = (rand()*rand()) % lc;
	int found;
	for (int i = 0; i<x; i++){
		found = (rand()*rand()) % lc;
		if (ratings[found] > ratings[best])
			best = found;
	}
	return best;
}

void GeneticClass::Crossover(int parent1, int parent2, vector<int> &child1, vector<int> &child2){
	int child1Size, child2Size, cutpoint1, cutpoint2;
	int parsiz1 = chromosom[parent1].size();
	int parsiz2 = chromosom[parent2].size();
	do
	{
		cutpoint1 = rand() % chromosom[parent1].size();
		cutpoint2 = rand() % chromosom[parent2].size();

		child1Size = cutpoint1 + chromosom[parent2].size() - cutpoint2;
		child2Size = cutpoint2 + chromosom[parent1].size() - cutpoint1;
	} while ((child2Size > GraphClass::vertex) || (child1Size > GraphClass::vertex));

	child1.resize(GraphClass::vertex);
	child2.resize(GraphClass::vertex);

	copy(chromosom[parent1].begin(), chromosom[parent1].begin() + cutpoint1, child1.begin());
	copy(chromosom[parent2].begin() + cutpoint2, chromosom[parent2].end(), child1.begin() + cutpoint1);

	copy(chromosom[parent2].begin(), chromosom[parent2].begin() + cutpoint2, child2.begin());
	copy(chromosom[parent1].begin() + cutpoint1, chromosom[parent1].end(), child2.begin() + cutpoint2);	

	child1.resize(cutpoint1 + chromosom[parent2].size() - cutpoint2);
	child2.resize(cutpoint2 + chromosom[parent1].size() - cutpoint1);
	repair(child1, child2);
}	

void GeneticClass::repair(vector <int> &chrom1, vector<int> &chrom2)
{
	vector <bool> visited(GraphClass::vertex, false);
	int dnaLen = 10;						//TODO: zamienic na zmienna
	bool cut = false;
	for (int i = 1; i < chrom1.size(); i++)
	{

		if (visited[chrom1[i]])
		{
			cut = true;
			for (int j = 0; j < nastepniki[chrom1[i - 1]].size(); j++)
			{

				if (!visited[nastepniki[chrom1[i - 1]][j][0]])
				{
					chrom1[i] = nastepniki[chrom1[i - 1]][j][0];
					cut = false;
					break;
				}
			}
		}
		dnaLen += GraphClass::matrix[chrom1[i - 1]][chrom1[i]];
		visited[chrom1[i]] = true;
		if ((dnaLen > Loader::optimum) || (cut == true))
		{
			chrom1.resize(i);					//TODO: Resize do i-1 czy i-2 ??
			break;
		}
	}

	dnaLen = 10;
	fill(visited.begin(), visited.end(), false);
	cut = false;
	for (int i = 1; i < chrom2.size(); i++)
	{
		if (visited[chrom2[i]])
		{
			cut = true;
			for (int j = 0; j < nastepniki[chrom2[i - 1]].size(); j++)
			{
				if (!visited[nastepniki[chrom2[i - 1]][j][0]])
				{
					chrom2[i] = nastepniki[chrom2[i - 1]][j][0];
					cut = false;
					break;
				}
			}
		}
		dnaLen += GraphClass::matrix[chrom2[i - 1]][chrom2[i]];
		visited[chrom2[i]] = true;
		if (dnaLen > Loader::optimum || (cut == true))
		{
			chrom2.resize(i - 1);				//TODO: Resize do i-1 czy i-2 ??
			break;
		}
	}
}

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
	srand(time(NULL));
	int length = chromosome.size();
	int index = rand() % length;
	int checkVertex = chromosome[index];
	int successorsAmount = nastepniki[checkVertex].size();
	
	if ((index != length-1) && (GraphClass::matrix[checkVertex][chromosome[index + 1]] != nastepniki[checkVertex][0][1])) 
		// Jezeli wylosowany wierzcholek nie jest ostatni i jego nastepnik w chromosomie nie jest najlepszy to buduj od tego miejsca
	{
		vector<bool> visited(GraphClass::vertex, false);
		unsigned int dnaLen = 10;												//TODO: Zamienic 10 na jakies pole w klasie uzupelniane przy wczytywaniu pliku
		for (int i = 0; i < index; i++)
		{
			visited[chromosome[i]] = true;
			dnaLen += GraphClass::matrix[chromosome[i]][chromosome[i + 1]];
		}
		visited[index] = true;
		chromosome.resize(GraphClass::vertex);
		createChromosom(index + 1, visited, chromosome, dnaLen, false);
	}
}

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

	if ((bestScoreInAll < bestRating) || (bestScoreInAll == 0))
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
	lc = 5000;                        

	int algorithmIteration = 20;
	int score = 0, parent1, parent2;

	DrawingPopulation();
	Rating();
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

		chromosom.swap(children);						//zakomentowany swap bo zakomentowane krzyzowanie // 
		/*
		int mutationIteration = 3000;
		for (int i = 0; i<mutationIteration; i++){
			int target = TournamentSelection(10);
			Mutation(chromosom[target]);//chromosom[target]);				//		przy zakomentowanym krzyzowaniu wpisalem tu chromosom zamiast children //
		} 
		*/
	
		score = Rating();
		cout << "Populacja_" << z << "  = " << score << endl;
	}

//	Mutation(path);
	showBest();
}

GeneticClass::~GeneticClass(){
}