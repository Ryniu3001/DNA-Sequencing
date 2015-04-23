#include "graf.hpp"


using namespace std;

int GraphClass::vertex;
vector<vector<int>> GraphClass::matrix = initializer_list<vector<int>>();

GraphClass Graph;
void GraphClass::create(){

	for (int i = 0; i < vertex; i++){
		vector<int> row;
		for (int j = 0; j < vertex; j++)
			row.push_back(0);
		matrix.push_back(row);
	}
//Losowanie wag
};

void GraphClass::calculateWeight(const vector<string> &data){
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data.size(); j++)
		{
			if (i != j)
			{
				for (int k = 0; k < GraphClass::DEPTH; k++)
				{
					int d = k + 1;
					string subStr = data[i].substr(d, data[i].length() - d);
					string subStr2 = data[j].substr(0, data[j].length() - d);
					if (subStr.compare(subStr2) == 0)
					{
						matrix[i][j] = d;
						break;
					}
				}
			}
		}

	}

	for (int i = 0; i < Loader::data.size(); i++)		//TYMCZASOWE rozwiazanie aby algortym nie bral pod uwage krawedzi z wag¹ 0. Jesli wezmie to bedzie to od razu widac po sumie wag.
	{
		for (int j = 0; j < Loader::data.size(); j++)
		{
			if (matrix[i][j] == 0)
				matrix[i][j] = 1000;
		}
	}
};

void GraphClass::print(){
    for (int i=0; i<vertex; i++){
        cout << endl;
        for (int j=0; j<vertex; j++)
            cout << matrix[i][j] << " ";
    }

};

GraphClass::~GraphClass(){
}
