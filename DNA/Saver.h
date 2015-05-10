#ifndef _SAVER_H
#define _SAVER_H
#include <vector>
#include <string>
#include "include/dirent.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;

class Saver
{
public:
	static int result;
	static int dnaLength;
	static int count;
	
	void write();
	Saver(string fileName);
	~Saver();

private:
	string file;
	clock_t start;
	clock_t stop;
	double time;
	ofstream out;

	void saveToFile();

};

#endif