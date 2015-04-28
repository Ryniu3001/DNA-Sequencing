#ifndef _LOADER_H
#define _LOADER_H
#include <vector>
#include <string>
#include "include/dirent.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;

class Loader
{

public:
	static int optimum;
	static vector<string> readFromFile();
	static void show();
	static void showTime(clock_t start, clock_t stop);

	Loader();
	~Loader();
private:
	static string getFileName();
};
#endif
