#pragma once
#include <stdio.h>
#include "StringList.h"

/*void CapsOn(string temp)
{
	int i, j = strlen((const char*)Asm_name);
	for (i = 0; i < j; i++)
	{
		if ((int)Asm_name[i] >= 97 && (int)Asm_name[i] <= 122)
		{
			(char)Asm_name[i] = (int)Asm_name[i] - 32;
		}
	}
}
*/

bool FileToList(string filename, StringList *Temp);
