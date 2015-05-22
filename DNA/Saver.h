#ifndef _SAVER_H
#define _SAVER_H
#include <vector>
#include <string>
#include "include/dirent.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>
#include "Loader.h"

using namespace std;

class Saver
{
public:
	static int result;
	static int dnaLength;
	static int count;
	static double average;
	static double minimum;
	static void rate();
	
	void write();
	Saver(string fileName);
	~Saver();

private:
	string file;
	clock_t start;
	clock_t stop;
	double time;
	ofstream out;
	double procent;

	void saveToFile();

};

#endif