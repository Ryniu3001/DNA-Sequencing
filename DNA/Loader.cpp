#include "Loader.h"


Loader::Loader()
{
	
}


Loader::~Loader()
{
}


void Loader::readFromFile(){
	string fileName = Loader::getFileName();
	ifstream file(".\\resources\\" + fileName);
	string line;
	while (getline(file, line)) {
		if (!line.empty())
			Loader::data.push_back(line);
	}
}


 string Loader::getFileName(){
	string result;
	DIR *dir;
	struct dirent *entry;
	if ((dir = opendir(".\\resources\\")) != NULL) {
		while ((entry = readdir(dir)) != NULL){
			if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
				result = entry->d_name;
		}
		closedir(dir);
	}
	else {
		perror("Nie mo¿na otworzyæ folderu");
	}
	return result;
}

 void Loader::show(){
	 for (int i = 0; i < Loader::data.size(); i++)
		 cout << Loader::data[i] << endl;
 }