#include "Greedy.h"

Greedy::Greedy()
{
	visited = new bool[GraphClass::vertex];
	for (int i = 0; i<GraphClass::vertex; ++i)
		visited[i] = false;
}

void Greedy::dfs(int x)
{
	bestResult.push_back(x);
	visited[x] = true;
	//cout <<x <<":\t";
	int minTime = INT_MAX, minIndex = -1;
	for (int i = 0; i<GraphClass::vertex; i++)
	{
		if (GraphClass::matrix[x][i] && !visited[i])
		{
			if (minTime >= GraphClass::matrix[x][i])
			{
				minTime = GraphClass::matrix[x][i];
				minIndex = i;
			}
		}
	}
	if (minIndex != -1)
	{
		pathTime += minTime;
		dfs(minIndex);
		return;
	}
	else
	{
		pathTime += GraphClass::matrix[x][0];
	}
}

void Greedy::start(int x, int time)
{
	bestResult.clear();
	pathTime = 0;
	for (int i = 0; i<GraphClass::vertex; i++)
		visited[i] = false;
	dfs(x);
}

void Greedy::printResult()
{
	cout << "\nZachlanny - Minimalny czas: " << pathTime << "\n";
	//for (int i = 0; i < bestResult.size(); ++i)
	//{
	//	cout << bestResult[i] << " ";
	//}
	cout << "\n";
}

Greedy::~Greedy()
{
}
