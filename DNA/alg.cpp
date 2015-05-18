#include "alg.hpp"

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

	nastepniki.clear();
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
			if (GraphClass::matrix[i][j] != 10){
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
	#pragma omp parallel for	
	for (int i = 0; i < lc; i++){
		vector <bool> visited(GraphClass::vertex,false);
		chromosom[i][0] = rand() % GraphClass::vertex;							//poczatkowy wierzcholek
		/* 
			Wedlug mnie bez sensu bo jak nastepniki beda mialy size = 0 to petla bedzie nieskonczona bo zadna zmienna sie nie zmienia
			Jak czasem sie zdazy chromosom o rozmiarze 1 to chyba nic nam nie szkodzi ;p 
		do chromosom[i][0] = i % GraphClass::vertex;							
		while (nastepniki[chromosom[i][0]].size() == 0);
		*/
		visited[chromosom[i][0]] = true;
		unsigned int dnaLen = 10;											//TODO: zmienic 10 na jakas zmienna czy cos
		int j = 1;

		createChromosom(j, visited, chromosom[i], dnaLen, !(i<(GraphClass::vertex * 0.01)));			//losowo - true, deterministycznie - !(i < GraphClass::vertex)
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
	visited[chrom1[0]] = true;
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
			chrom1.resize(i);					
			break;
		}
	}

	dnaLen = 10;
	fill(visited.begin(), visited.end(), false);
	cut = false;
	visited[chrom2[0]] = true;
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
			chrom2.resize(i - 1);				
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

//Poprzednia mutacja
void GeneticClass::makeBetterMutation(vector<int> &chromosome){


	int index1 = -1;
	int index2 = -1;
	int node = -1;
	for (int i = 0; i < (chromosome.size() - 1); i++){
		int current = chromosome[i];
		int next = chromosome[i + 1];
		int size = nastepniki[current].size() - 1;

		for (int j = 0; j < size; j++){
			if (nastepniki[current][j][0] == next){
				if (nastepniki[current][j][1] == nastepniki[current][j + 1][1]){
					node = nastepniki[current][j + 1][0];
					break;
				}
			}
		}

		if (node > 0){
			index1 = i + 1;
			for (int j = 0; j < chromosome.size(); j++){
				if (chromosome[j] == node){
					index2 = j;
					break;
				}
			}
			break;
		}
	}

	if (index1 >= 0){
		if (index2 > 0)
			chromosome[index1] = chromosome[index2];
		else
			chromosome[index1] = node;


		vector<bool> visited(GraphClass::vertex);
		int rate = 10;
		visited[chromosome[0]] = true;
		for (int i = 0; i < index1; i++){
			int current = chromosome[i];
			int next = chromosome[i + 1];
			rate += GraphClass::matrix[current][next];
			visited[next] = true;
		}
		chromosome.resize(GraphClass::vertex);
		createChromosom(index1 + 1, visited, chromosome, rate, false);
	}	
}

void GeneticClass::Mutation(vector<int> &chromosome){
	srand(time(NULL));
	int length = chromosome.size();
	int index = rand() % (length);				//TODO: Jak length-1 == 0 to bedzie wyskakiwal wyjatek
	int checkVertex = chromosome[index];
	int successorsAmount = nastepniki[checkVertex].size();

	bool sterowane = false;
	if ((rand() % 10) == 0)
		sterowane = true;

	if (!sterowane && (index != length - 1) && (GraphClass::matrix[checkVertex][chromosome[index + 1]] != nastepniki[checkVertex][0][1]))
		// Jezeli dla wylosowanego wierzcholka, nastepnik w chromosomie nie jest najlepszy to buduj od tego miejsca //TODO: mog¹ byæ powtórzenia !!!!!!!!!!!!!!!
	{
		vector<bool> visited(GraphClass::vertex, false);
		unsigned int dnaLen = 10;												//TODO: Zamienic 10 na jakies pole w klasie uzupelniane przy wczytywaniu pliku
		for (int i = 0; i < index; i++)
		{
			visited[chromosome[i]] = true;
			dnaLen += GraphClass::matrix[chromosome[i]][chromosome[i + 1]];
		}
		visited[checkVertex] = true;
		chromosome.resize(GraphClass::vertex);
		createChromosom(index + 1, visited, chromosome, dnaLen, true);
	} 
	else if ((index != length - 1) && (nastepniki[checkVertex][0][1] == nastepniki[checkVertex][1][1]))
		// jezeli ma 2 najlepsze nastepniki i nie bylo zmiany
	{
		cout << "MAM DWA NAJLEPSZE" << endl;
		index++;
		int index2 = -1;
		int toChange = nastepniki[checkVertex][1][0];

		for (int j = 0; j < chromosome.size(); j++){						// sprawdzamy czy byl uzyty drugi najlepszy nastepnik w chromosomie
			if (chromosome[j] == toChange){
				index2 = j;
				break;
			}
		}

		if (index2 > 0){												
			if (index < index2)												
				chromosome[index] = chromosome[index2];
			else{															// jesli jest przed obecnym indexem to zamieniamy we wczesniejszym miejscu w chromosomie
				chromosome[index2] = chromosome[index];
				index = index2;												// miejsce dla visited
			}
		}
		else
			chromosome[index] = toChange;

		vector<bool> visited(GraphClass::vertex, false);
		unsigned int dnaLen = 10;												//TODO: Zamienic 10 na jakies pole w klasie uzupelniane przy wczytywaniu pliku
		for (int i = 0; i < index; i++)
		{
			visited[chromosome[i]] = true;
			dnaLen += GraphClass::matrix[chromosome[i]][chromosome[i + 1]];
		}
		visited[chromosome[index]] = true;
		chromosome.resize(GraphClass::vertex);
		createChromosom(index + 1, visited, chromosome, dnaLen, false);
	}
	else if (sterowane)
		makeBetterMutation(chromosome);
}

int GeneticClass::Rating()
{
	int bestRating = -1, bestChromosom = -1;
	vector<int> chromosomBestPath;
	fill(ratings.begin(), ratings.end(), 0);
	for (int i = 0; i<lc; i++){
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
	int dnaLength = printBest();
	double procent = (100.0 * bestScoreInAll) / (Loader::optimum - 9);
	cout << endl << "Uzyskany najlepszy wynik: " << bestScoreInAll << endl;
	cout << "Uzyskana dlugosc DNA: " << dnaLength << endl;
	cout << "Uzyskany procent: " << procent << "% " << endl;
	cout << "-------------------------------" << endl << endl;

	Saver::dnaLength = dnaLength;
	Saver::result = bestScoreInAll;
}

int GeneticClass::printBest(){
	int dnaLength = 10;
	for (int i = 0; i<path.size(); i++){
		if (i > 0)
		{
		//	cout << " <" << GraphClass::matrix[path[i - 1]][path[i]] << "> " << path[i];
			dnaLength += GraphClass::matrix[path[i - 1]][path[i]];
		}
		else
		{
		//	cout << path[i];
		}
	}
	return dnaLength;
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
//	cout << "SPRAWDZAMY POWTORZENIA IN SET ... ";
	for (int i = 0; i < lc; i++){
		vector<bool> visited(GraphClass::vertex);
		for (int j = 0; j < chromosom[i].size(); j++){
			if (!visited[chromosom[i][j]])
				visited[chromosom[i][j]] = true;
			else{
				for (int k = 0; k < chromosom[i].size(); k++)
					if (chromosom[i][j] == chromosom[i][k])
						break;
				cout << endl << "W CHROMOSOMIE " << i << " S¥ POWTORZENIA" << endl;
			}
		}
	}
//	cout << "KONIEC" << endl << endl;
}

///////////////////////////////  INTERFACE  ////////////////////////////////
void GeneticClass::Interface(){
	lc = 1000;                        

	int algorithmIteration = 30;
	int score = 0, parent1, parent2;

	DrawingPopulation();
	Rating();
	cout << "Rodzice: " << bestScoreInAll << endl;
	checksRepeatsInSet();

	////////////// SELEKCJA I KRZYZOWANIE I MUTACJA///////////////////////////////
	for (int z = 0; z<algorithmIteration; z++){
		int P = -1;		                            // licznik nowej populacji
		
		float crossoverRatio = 0.3;
		vector<bool> crossed(lc,false);
		int crossoverIterations = (lc - 2) * crossoverRatio;
		#pragma omp parallel for
		for (P = -1; P < crossoverIterations; P += 2)
		{
			parent1 = TournamentSelection(10);
			do
				parent2 = TournamentSelection(10);
			while (parent1 == parent2);
			crossed[parent1] = true;
			crossed[parent2] = true;
			Crossover(parent1, parent2, children[P + 1], children[P + 2]);
		}

		for (int i = 0 ; i < lc; i++)					//Dopisuje do children osobniki ktore nie braly udzialu w krzyzowaniu
		{
			if (crossoverIterations != lc)
			{
				if (crossed[i] == false)
				{
					children[crossoverIterations++] = chromosom[i];
				}
			}
			else
			{
				break;
			}
		}

		chromosom.swap(children);						
		
		int mutationIteration = 10;
		for (int i = 0; i<mutationIteration; i++){
			int target = TournamentSelection(100);
			Mutation(chromosom[target]);			//	przy zakomentowanym krzyzowaniu wpisalem tu chromosom zamiast children 
		}

		checksRepeatsInSet();
	
		score = Rating();
		cout << "Populacja_" << z << " = " << score << endl;
	}

//	Mutation(path);
	showBest();
}

GeneticClass::~GeneticClass(){
}