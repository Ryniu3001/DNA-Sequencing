#ifndef generator_h
#define generator_h

#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

class Generator
{
public:
	vector<string> dna;

	Generator();
	~Generator();

private:
	int number, type;
	static const int lenght = 10;

	void interface();
	void generujDNA();
	void makePositives();
	void makeNegatives();
	void mix();
	void choosenOption();
	void saveToFile();
};

#endif