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
	int minus = 0;
	size_t begin = name.find(".");
	size_t end = name.find("-");
	if (end == string::npos)
		end = name.find("+");

	begin++;
	end -= 2;
	string number = name.substr(begin, end);	
	istringstream iss(number);
	iss >> result;
	result += 9;
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

 void Loader::showTime(clock_t start, clock_t stop){
	 cout << "Czas: " << (stop - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl << endl;
 }