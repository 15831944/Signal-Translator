#include "FileToList.h"

#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <QFile>
#include <QTextStream>

#pragma warning (disable : 4996) 

using namespace std;

bool FileToList(string filename, StringList *Temp)
{
	setlocale(LC_ALL, "rus");
    //ifstream file;
    QFile file(filename.c_str());
	string line;
	string temp;
	int pos;
	int input_id;

    //file.open(QIODevice::ReadOnly);


    if (!file.open(QIODevice::ReadOnly))
	{
		cout << "Файл не открыт\n\n";
		file.close();
		return false;
	}

    QTextStream stream(&file);

    while (!stream.atEnd())
	{
        //getline(file, line);
        line = (string)stream.readLine().toUtf8().constData();
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
