#pragma once
#include "StringList.h"
#include <iostream>
#include "FileToList.h"
#include "ASCII.h"
#include <fstream>
#include <string>

class Syntax 
{
public:

	Syntax(string input_file_name);
	~Syntax() {};
	bool isError() 
	{
		return Error;
	}

    const char * GetErrorM()
    {
        return Err.c_str();
    }

	struct All_in_One
	{
		StringList Data;

		StringList Identifiers;

		StringList Constants; // pi

		StringList SingleChar; // ; : ) ( ...

		StringList Keywords; //Begin 
	}All;
private:
	bool Error;
	string Err;

	bool Syntax_Analize(All_in_One &, const string);

	bool isAlphabetError(const char);

	int GetCategory(char &a, All_in_One);
};
