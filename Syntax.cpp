#include "Syntax.h"
#include "QFile"
#include "QTextStream"

Syntax::Syntax(string input_file_name)
{
	Error = false;

    if (!FileToList("C:\\Users\\0137\\Desktop\\SignalTranslator\\Resource\\SingleChar.txt", &All.SingleChar))
	{
		cout << "Error";
		Error = true;
		return;
	}

    if (!FileToList("C:\\Users\\0137\\Desktop\\SignalTranslator\\Resource\\Keywords.txt", &All.Keywords ))
	{
		cout << "Error";
		Error = true;
		return;
	}

    Syntax_Analize(All, input_file_name);
}

bool Syntax::isAlphabetError(const char a, int ipos, int jpos)
{

	if ((char)a != ASCII[(int)a])
	{
			Error = true;
            Err = "Error, unknown symbol : \"";
            Err +=(char)a;
			Err += "\" on pos: (";
            Err	+= to_string(ipos);
            Err += ',';
            Err += to_string(jpos);
            Err += ")";
			return true;
	}
	
	return false;
}

int Syntax::GetCategory(char &a, All_in_One All,int ipos,int jpos)
{
    if (isAlphabetError(a, ipos, jpos))
	{
		return 6;
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
    //ifstream file;
    QFile file(input_file_name.c_str());
	char a;
	string line;
	string elem;
	int ipos = 0;
	int jpos = 0, jpos_temp = 0;
	ListNode *temp;

    //file.open("Resource/" + input_file_name + ".txt");

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
		jpos = 0;
		while (line[jpos] != '\0')
		{
			a = line[jpos];
			start:
            switch (GetCategory(a, All, ipos, jpos))
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

                while (!stream.atEnd() && (int)a >= 48 && (int)a <= 57 )
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
                    if ((int)a >= 97 && (int)a <= 122)
                    {
                        a = (int)a - 32;
                    }
                    if (GetCategory(a, All, ipos, jpos) == 6)
                    {
                        return true;
                    }
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
                    temp = (ListNode*)All.Identifiers.Find(elem.c_str());
                    if (temp == nullptr)
                    {
                        if (All.Identifiers.IsEmpty())
                        {
                            All.Identifiers.AddTail(elem.c_str(), 400);
                        }
                        else
                        {
                            All.Identifiers.AddTail(elem.c_str(), All.Identifiers.GetLastId() + 1);
                        }
                    }
                    //All.Keywords.AddTail(elem.c_str(), All.Keywords.GetLastId() + 1);
                    All.Data.AddTail(elem.c_str(), All.Identifiers.GetLastId(), ipos, jpos_temp);
				}
				if (All.SingleChar.Find(&a) != nullptr)
				{
					jpos--;
				}
				break;

			}
			case 3: // Односимвольні роздільники 
			{
                //из-за мусора в односимвольных разделителях юзаем костыль
                elem.clear();
                elem = a;
                elem.erase(1,elem.length()-2);

                All.Data.AddTail(elem.c_str(), (int)a, ipos, jpos);
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
                    while (!stream.atEnd())
					{
						a = line[jpos];
						if (a == '\0')
						{
                            //getline(file, line);
                            line.clear();
                            line = (string)stream.readLine().toUtf8().constData();
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
                                if (a != '\0' && !stream.atEnd())
								{
									goto start;
								}
								jpos--;
                                bkt = true;
								break;
							}

						}
						jpos++;
					}
                    if (!bkt)
                    {
                        Error = true;
                        Err = "Illigal comment";
                        line.clear();
                        line[jpos+1] = '\0';
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

