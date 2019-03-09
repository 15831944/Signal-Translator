#include "FileToList.h"

#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>

#pragma warning (disable : 4996) 

using namespace std;

bool FileToList(string filename, StringList *Temp)
{
	setlocale(LC_ALL, "rus");
	ifstream file;
	string line;
	string temp;
	int pos;
	int input_id;

	file.open("Resource/" + filename);


	if (!file.is_open())
	{
		cout << "Файл не открыт\n\n";
		file.close();
		return false;
	}

	while (!file.eof())
	{
		getline(file, line);
		pos = line.find("|");
		temp = line.substr(0, pos);
		line = line.substr(pos + 1,  line.find("|", pos + 1) );
		line.erase(line.length() - 1, 1);
		input_id = atoi(line.c_str());
		Temp->AddTail(temp.c_str(), input_id);
	}

	file.close();
	return true;
}
