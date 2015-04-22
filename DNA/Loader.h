#ifndef _LOADER_H
#define _LOADER_H
#include <vector>
#include <string>
#include "include/dirent.h"
#include <fstream>
#include <iostream>

using namespace std;


class Loader
{

public:
	static vector<string> data;
	static void readFromFile();
	static void show();

	Loader();
	~Loader();
private:
	static string getFileName();
};
#endif
