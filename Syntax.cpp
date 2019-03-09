#include "Syntax.h"

Syntax::Syntax(string input_file_name)
{
	Error = false;

	if (!FileToList("SingleChar.txt", &All.SingleChar))
	{
		cout << "Error";
		Error = true;
		return;
	}

	if (!FileToList("Keywords.txt", &All.Keywords ))
	{
		cout << "Error";
		Error = true;
		return;
	}

	//All.SingleChar.Find(";");

	if (!Syntax_Analize(All, input_file_name));
}

bool Syntax::isAlphabetError(const char a) 
{
	int ipos = 0;
	int jpos = 0;

	if ((char)a != ASCII[(int)a])
	{
			Error = true;
			Err = "Error, unknown symbol : \"" + (char)a;
			Err += "\" on pos: (";
			Err	+= to_string(ipos) + ' ';
			Err += to_string(jpos) + ")";
			return true;
	}
	
	return false;
}

int Syntax::GetCategory(char &a, All_in_One All)
{
	if (isAlphabetError(a))
	{
		return 6;
	}
	else if ((int)a >= 97 && (int)a <= 122)
	{
		a = (int)a - 32;
		return 2;
	}
	else if ((int)a >= 65 && (int)a <= 90)
	{
		return 2;
	}
	else if (a == '(')
	{
		return 5;
	}
	else if (All.SingleChar.Find(&a))
	{
		return 3;
	}


	return 0;
}

bool Syntax::Syntax_Analize(All_in_One &All,
	const string input_file_name)
{
	ifstream file;
	char a;
	string line;
	string elem;
	int ipos = 0;
	int jpos = 0, jpos_temp = 0;
	ListNode *temp;

	file.open("Resource/" + input_file_name + ".txt");

	if (!file.is_open())
	{
		cout << "Файл не открыт\n\n";
		file.close();
		return false;
	}

	while (!file.eof())
	{
		getline(file, line);
		jpos = 0;
		while (line[jpos] != '\0')
		{
			a = line[jpos];
			start:
			switch (GetCategory(a, All))
			{
			case 0: //Пробільні символи (whitespace): пробіл (space) – 32; прирівняні до пробілів – 8, 9, 10, 13 
			{
				//All.Data.AddTail(&a, (int)a, ipos, jpos);
				break;
			}
			case 1: //Символи, з яких можуть починатися константи
			{
				elem.clear();
				a = line[jpos];
				jpos_temp = jpos;

				while (!file.eof() && (int)a >= 48 && (int)a <= 57 )
				{
					elem += a;
					jpos++;
					a = line[jpos];
				}
				break;
			}
			case 2: //Символи, з яких можуть починатися ідентифікатори та ключові слова 
			{
				elem.clear();
				a = line[jpos];
				jpos_temp = jpos;

				while (a != '\0' && All.SingleChar.Find(&a) == nullptr  && a != ' ' && a != '\n')
				{
					elem += a;
					jpos++;
					if (jpos < line.length())
					{
						a = line[jpos];
					}
					else
					{
						jpos--;
						break;
					}
					
				}
				temp = (ListNode*)All.Keywords.Find(elem.c_str());

				if (temp != nullptr)
				{
					All.Data.AddTail(temp->str, temp->id, ipos, jpos_temp);
				}
				else
				{
					All.Keywords.AddTail(elem.c_str(), All.Keywords.GetLastId() + 1);
					All.Data.AddTail(elem.c_str(), All.Keywords.GetLastId(), ipos, jpos_temp);
				}
				if (All.SingleChar.Find(&a) != nullptr)
				{
					jpos--;
				}
				break;

			}
			case 3: // Односимвольні роздільники 
			{
				All.Data.AddTail(&a, (int)a, ipos, jpos);
				break;
			}
			case 4: // Символи, з яких можуть починатися багатосимвольні роздільники (таких категорій може бути декілька) 
			{
				break;
			}
			case 5: // Символи, з яких можуть починатися коментарі (таких категорій може бути декілька)
			{
				elem.clear();
				elem += a;
				bool bkt = false;
				jpos++;
				if (line[jpos] == '*')
				{
					while (!file.eof())
					{
						a = line[jpos];
						if (a == '\0')
						{
							getline(file, line);
							jpos = 0;
							a = line[jpos];
							ipos++;
						}
						if (a == '*')
						{
							jpos++;
							a = line[jpos];
							if (a == ')')
							{
								jpos++;
								a = line[jpos];
								if (a != '\0')
								{
									goto start;
								}
								jpos--;
								break;
							}

						}
						jpos++;
					}
				}
				else
				{
					All.Data.AddTail(elem.c_str(), (int)a, ipos, jpos-1);
					a = line[jpos];
					goto start;
				}

				break;
			}
			case 6: // Недопустимі символи
			{
				return true;
			}
			default:
				break;
			}
			jpos++;
		}
		ipos++;
		
	}


	return false;
}

