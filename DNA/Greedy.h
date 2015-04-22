#ifndef GREEDY_H
#define GREEDY_H
#include <iostream>
using namespace std;
#include <vector>
#include <Climits>
#include "graf.hpp"


class Greedy
{
private:
	bool *visited;
	vector<int> result;
	vector<int> bestResult;
	int pathTime;
public:
	Greedy();
	void start(int x, int time);
	void dfs(int x);
	void printResult();
	virtual ~Greedy();
};

#endif // GREEDY_H