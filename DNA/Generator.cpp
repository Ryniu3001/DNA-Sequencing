#include "Generator.h"

string getLetter(int i){
	switch (i){
		case 0:
			return "T";
		case 1:
			return "C";
		case 2:
			return "A";
		case 3:
			return "G";
	}
}

void Generator::interface(){
	srand(time(NULL));
	cout << "Podaj wielkosc instancji: " << endl;
	cin >> number;
	name = "." + to_string(number);
	cout << "Podaj typy bledow: 1-NEG, 2-POZ, 3-OBA" << endl;
	cin >> type;
}

void Generator::generujDNA(){
	string first = ""; 
	for (int i = 0; i < lenght; i++){
		first += getLetter(rand() % 4);
	}
	dna.push_back(first);
	
	for (int i = 1; i < number; i++){
		string next = dna[i-1].substr(1);
		next += getLetter(rand() % 4);
		dna.push_back(next);
	}
}

void Generator::makePositives(){
	int num;
	cout << "Podaj liczbe bledow pozytywnych: " << endl;
	cin >> num;
	name += "+" + to_string(num);

	for (int i = 0; i < num; i++){
		string oli = "";
		for (int i = 0; i < lenght; i++){
			oli += getLetter(rand() % 4);
		}
		dna.push_back(oli);
	}
}

void Generator::makeNegatives(){
	int num;
	cout << "Podaj liczbe bledow negatywnych: " << endl;
	cin >> num;
	name += "-" + to_string(num);

	for (int i = 0; i < num; i++){
		int that = (rand() % dna.size());
		dna.erase(dna.begin() + that);
	}
}

void Generator::choosenOption(){
	switch (type){
	case 1:
		makeNegatives();
		break;
	case 2:
		makePositives();
		break;
	case 3:
		makeNegatives();
		makePositives();
		break;
	default:
		cout << "ERROR" << endl;
		break;
	}
}

void Generator::mix(){
	vector<string> tmpDNA;
	vector<bool> visited(dna.size());
	for (int i = 0; i < dna.size(); i++){
		int that = rand() % dna.size();
		if (visited[that]) 
		{
			int i = 0;
			while (true){
				if (visited[i])
					i++;
				else
					break;
			}
			that = i;
		}
		visited[that] = true;
		tmpDNA.push_back(dna[that]);
	}
	dna = tmpDNA;
}

void Generator::saveToFile(){
	string nameFile;
	cout << "Podaj nazwe pliku: " << endl;
	cin >> nameFile;
	string file = ".\\resources\\" + nameFile + name + ".txt";

	ofstream out(file);


	for (int i = 0; i < dna.size(); i++){
		out << dna[i] << endl;
	}
	out.close();
}


Generator::Generator()
{
	interface();	
	generujDNA();
	choosenOption();
	mix();
	saveToFile();
}

Generator::~Generator()
{
}
