#include "Saver.h"

int Saver::dnaLength = -1;
int Saver::result = -1;
int Saver::count = 0;

void Saver::write(){
	stop = clock();
	time = (stop - start) / (double)(CLOCKS_PER_SEC / 1000);
	count++;
	procent = (100.0 * result) / (Loader::optimum - 9);
	saveToFile();
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
	out << "-------------------------------" << endl;
	out << file << endl;
	out << time << "ms" << endl;
	out << "U¿ytych: " << result << endl;
	out << "D³ugoœæ: " << dnaLength << endl;
	out << "Procent: " << procent << endl;
	out << "-------------------------------" << endl;

	out.close();
}