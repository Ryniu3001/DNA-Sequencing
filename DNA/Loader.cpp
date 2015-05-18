#include "Loader.h"

Loader::Loader()
{
}


Loader::~Loader()
{
}

int Loader::optimum = 0;
vector<string> Loader::fileNames = initializer_list<string>();

int getOptimum(string name){
	int result = -1;
	int minus = 0, plus = 0;
	size_t begin = name.find(".");
	size_t end_minus = name.find("-");
	size_t end_plus = name.find("+");
	int end;
	if (end_minus != string::npos)
		end = end_minus;
	else
		end = end_plus;
	begin++;

	{
		string number = name.substr(begin, (end - begin));
		istringstream iss(number);
		iss >> result;
	}

	int  size = name.length();
	if ((end_minus != string::npos) && (end_plus != string::npos))
	{
		end_minus++;
		string number = name.substr(end_minus, (end_plus - end_minus));
		istringstream iss(number);
		iss >> minus;
	}
	else if (end_minus != string::npos)
	{
		end_minus++;
		string number = name.substr(end_minus, (size - end_plus));
		istringstream iss(number);
		iss >> minus;
	} 

	result += 9 + plus - minus;
	cout << "Optimum: " << result << endl << endl;

	return result;
}

vector<string> Loader::readFromFile(string fileName){
	vector<string> data;	
	
	ifstream file(".\\resources\\" + fileName);
	string line;
	while (getline(file, line)) {
		if (!line.empty())
			data.push_back(line);
	}
	cout << "Plik:" << "\t " << fileName << endl;
	Loader::optimum = getOptimum(fileName);

	return data;
}

void Loader::getFileNames(){
	DIR *dir;
	struct dirent *entry;
	if ((dir = opendir(".\\resources\\")) != NULL) {
		while ((entry = readdir(dir)) != NULL){
			if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
				fileNames.push_back(entry->d_name);
		}
		closedir(dir);
	}
	else {
		perror("Nie mo¿na otworzyæ folderu");
	}
}