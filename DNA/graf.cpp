#include "graf.hpp"


using namespace std;

int GraphClass::vertex;
vector<vector<int>> GraphClass::matrix = initializer_list<vector<int>>();

GraphClass Graph;
void GraphClass::create(){
	for (int i = 0; i < vertex; i++){
		vector<int> row;
		for (int j = 0; j < vertex; j++)
			row.push_back(1000);
		matrix.push_back(row);
	}
};

void GraphClass::calculateWeight(const vector<string> &data){
	for (int i = 0; i < data.size(); i++)
		for (int j = 0; j < data.size(); j++)
			if (i != j)
				for (int k = 0; k < GraphClass::DEPTH; k++)
				{
					int d = k + 1;
					string subStr = data[i].substr(d, data[i].length() - d);
					string subStr2 = data[j].substr(0, data[j].length() - d);
					if (!subStr.compare(subStr2))
					{
						matrix[i][j] = d-1;
						break;
					}
				}	
};

void GraphClass::print(){
    for (int i=0; i<vertex; i++){
        for (int j=0; j<vertex; j++)
            cout << matrix[i][j] << "\t";
		cout << endl;
    }

};

GraphClass::~GraphClass(){
}
