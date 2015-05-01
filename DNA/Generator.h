#ifndef generator_h
#define generator_h

#include <iostream>
#include <vector>
#include <ctime>
#include <string>

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

	void generujDNA();
	void makePositives();
	void makeNegatives();
	void mix();
};

#endif