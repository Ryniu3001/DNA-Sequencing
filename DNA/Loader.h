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

static class Loader
{

public:
	static int optimum;
	static int maxUsed;
	static vector<string> readFromFile(string fileName);

	static void getFileNames();
	static vector<string> fileNames;	
	static void countOptimum(string name);
	Loader();
	~Loader();


};
#endif
