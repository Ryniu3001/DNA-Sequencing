#include "Saver.h"

int Saver::dnaLength = -1;
int Saver::result = -1;
int Saver::count = 0;
double Saver::average = 0;
double Saver::minimum = -1;

void Saver::write(){
	stop = clock();
	time = (stop - start) / (double)(CLOCKS_PER_SEC / 1000);
	count++;
	procent = (100.0 * result) / (Loader::maxUsed);
	if ((minimum == -1) || (procent < minimum))
		minimum = procent;
	average += procent;
	saveToFile();
}

void Saver::rate(){
	cout << endl << endl << "Minimum: " << minimum << "% \t Srednia: " << (average / count) << "% " << endl;
}

Saver::Saver(string fileName)
{
	file = fileName;
	start = clock();
}

Saver::~Saver()
{
}

void Saver::saveToFile(){
	string name = ".\\testy\\Testy" + to_string(count) + ".txt";
	ofstream out(name);
	out << "Plik" << "\t" << file << endl;
	out << "Czas [ms]" << "\t" << time << endl;
	out << "U¿ytych " << "\t" << result << endl;
	out << "D³ugoœæ " << "\t" << dnaLength << endl;
	out << "Procent " << "\t" << procent << endl;
	out.close();
}