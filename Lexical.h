#pragma once
#include "StringList.h"
#include <iostream>
#include "FileToList.h"
#include "ASCII.h"
#include <string>
#include "Syntax.h"

const string SignalPath = "C:\\Users\\0137\\Desktop\\SignalTranslator\\Resource\\";

struct All_in_One
{
    StringList Data;

    StringList Identifiers; // <letter><string>

    StringList Constants; // pi numbers etc

    StringList SingleChar; // ; : ) ( ...

    StringList Keywords; //Begin SIGNAL
};

class Lexical
{
public:

    Lexical(string input_file_name);
    ~Lexical() {}
	bool isError() 
	{
		return Error;
	}

    const char * GetErrorM()
    {
        return Err.c_str();
    }

    struct All_in_One All;
private:
	bool Error;
	string Err;

    bool Lexical_Analize(All_in_One &, const string);

    bool isAlphabetError(const char, int ipos,int jpos);

    int GetCategory(char &a, All_in_One, int ipos,int jpos);

    void TransformTab(string &);
};
