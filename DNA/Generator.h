#ifndef generator_h
#define generator_h

#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>

using namespace std;

class Generator
{
public:
	vector<string> dna;

	Generator();
	~Generator();

private:
	static const int lenght = 10;
	string name;
	int number, type;
	
	void interface();
	void generujDNA();
	void makePositives();
	void makeNegatives();
	void mix();
	void choosenOption();
	void saveToFile();
};

#endif