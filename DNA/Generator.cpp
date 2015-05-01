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
		string next = first.substr(1);
		next += getLetter(rand() % 4);
		dna.push_back(next);
	}
}

void Generator::makePositives(){

}

void Generator::makeNegatives(){

}

void Generator::mix(){

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



Generator::Generator()
{
	interface();	
	generujDNA();
	choosenOption();
	mix();
}

Generator::~Generator()
{
}
