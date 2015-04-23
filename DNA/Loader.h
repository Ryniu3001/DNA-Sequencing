#ifndef _LOADER_H
#define _LOADER_H
#include <vector>
#include <string>
#include "include/dirent.h"
#include <fstream>
#include <iostream>
#include <ctime>

using namespace std;

class Loader
{

public:
	static vector<string> data;
	static void readFromFile();
	static void show();
	static void showTime(clock_t start, clock_t stop);

	Loader();
	~Loader();
private:
	static string getFileName();
};
#endif
