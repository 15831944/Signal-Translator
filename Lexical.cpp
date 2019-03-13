#include "Lexical.h"
#include "QFile"
#include "QTextStream"

Lexical::Lexical(string input_file_name)
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

    Lexical_Analize(All, input_file_name);
}

bool Lexical::isAlphabetError(const char a, int ipos, int jpos)
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

int Lexical::GetCategory(char &a, All_in_One All,int ipos,int jpos)
{
    if (a == '\'')//доп задание, потом уберу
    {
        return 4;
    }
    else if (isAlphabetError(a, ipos, jpos))
	{
		return 6;
	}
	else if ((int)a >= 65 && (int)a <= 90)
	{
		return 2;
    }
    else if ((int)a >= 97 && (int)a <= 122)
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
    else if ((int)a >= 48 && (int)a <= 57)
    {
        return 1;
    }


	return 0;
}

bool Lexical::Lexical_Analize(All_in_One &All,
	const string input_file_name)
{
    QFile file(input_file_name.c_str());

	char a;
    bool bkt = false;
	string line;
	string elem;
    int ipos = 0;
    int jpos = 0, jpos_temp = 0;
	ListNode *temp;

    if (!file.open(QIODevice::ReadOnly))
	{
		cout << "Файл не открыт\n\n";
		file.close();
		return false;
	}

    QTextStream stream(&file);

    while (!stream.atEnd())
	{
        line = (string)stream.readLine().toUtf8().constData();
        TransformTab(line);

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

                temp = (ListNode*)All.Constants.Find(elem.c_str());
                if (temp == nullptr)
                {
                    if (All.Constants.IsEmpty())
                    {
                        All.Constants.AddTail(elem.c_str(), 500);
                    }
                    else
                    {
                        All.Constants.AddTail(elem.c_str(), All.Constants.GetLastId() + 1);
                    }
                }
                All.Data.AddTail(elem.c_str(), All.Constants.GetLastId(), ipos, jpos_temp);

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
                    else if (GetCategory(a, All, ipos, jpos) == 6)
                    {
                        return true;
                    }
                    else if(GetCategory(a, All, ipos, jpos) == 4)
                    {
                        jpos--;
                        break;
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
                    All.Data.AddTail(temp->str, temp->id, ipos+1, jpos_temp+1);
				}
                else
				{
                    temp = (ListNode*)All.Identifiers.Find(elem.c_str());
                    if (temp == nullptr)
                    {
                        if (All.Identifiers.IsEmpty())
                        {
                            All.Identifiers.AddTail(elem.c_str(), 1001);
                        }
                        else
                        {
                            All.Identifiers.AddTail(elem.c_str(), All.Identifiers.GetLastId() + 1);
                        }
                    }
                    All.Data.AddTail(elem.c_str(), All.Identifiers.GetLastId(), ipos+1, jpos_temp+1);
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

                All.Data.AddTail(elem.c_str(), (int)a, ipos+1, jpos+1);
				break;
			}
            case 4: // доп задание: "дата" '2019-03-13'// Символи, з яких можуть починатися багатосимвольні роздільники (таких категорій може бути декілька)
			{
                int i;
                jpos_temp = jpos;
                jpos++;
                a = line[jpos];
                elem.clear();
                while (a != '\0')
                {
                    if ((int)a == 39)
                    {
                        break;
                    }
                    elem += a;
                    jpos++;
                    a = line[jpos];
                }

                for (i = 0; i<4; i++)
                {
                    if (GetCategory(elem[i], All, ipos, jpos_temp) == 1)
                    {
                        continue;
                    }
                    else
                    {
                        Error = true;
                        Err = "Incporrect Data on pos: (";
                        Err	+= to_string(ipos);
                        Err += ',';
                        Err += to_string(jpos_temp);
                        Err += ")";
                        return true;
                    }
                }
                if (elem[4] != '-')
                {
                    Error = true;
                    Err = "Incporrect Data on pos: (";
                    Err	+= to_string(ipos);
                    Err += ',';
                    Err += to_string(jpos_temp);
                    Err += ")";
                    return true;
                }

                for (i = 5; i<7; i++)
                {
                    if (GetCategory(elem[i], All, ipos, jpos_temp) == 1)
                    {
                        continue;
                    }
                    else
                    {
                        Error = true;
                        Err = "Incporrect Data on pos: (";
                        Err	+= to_string(ipos);
                        Err += ',';
                        Err += to_string(jpos_temp);
                        Err += ")";
                        return true;
                    }
                }
                if (elem[7] != '-')
                {
                    Error = true;
                    Err = "Incporrect Data on pos: (";
                    Err	+= to_string(ipos);
                    Err += ',';
                    Err += to_string(jpos_temp);
                    Err += ")";
                    return true;
                }

                for (i = 8; i< 10; i++)
                {
                    if (GetCategory(elem[i], All, ipos, jpos_temp) == 1)
                    {
                        continue;
                    }
                    else
                    {
                        Error = true;
                        Err = "Incporrect Data on pos: (";
                        Err	+= to_string(ipos);
                        Err += ',';
                        Err += to_string(jpos_temp);
                        Err += ")";
                        return true;
                    }
                }

                temp = (ListNode*)All.Identifiers.Find(elem.c_str());
                if (temp == nullptr)
                {
                    if (All.Identifiers.IsEmpty())
                    {
                        All.Identifiers.AddTail(elem.c_str(), 1001);
                    }
                    else
                    {
                        All.Identifiers.AddTail(elem.c_str(), All.Identifiers.GetLastId() + 1);
                    }
                    All.Data.AddTail(elem.c_str(), All.Identifiers.GetLastId(), ipos+1, jpos_temp+1);
                }
                else
                {
                    All.Data.AddTail(elem.c_str(), temp->id, ipos+1, jpos_temp+1);
                }

				break;
			}
			case 5: // Символи, з яких можуть починатися коментарі (таких категорій може бути декілька)
			{
				elem.clear();
				elem += a;
				jpos++;
				if (line[jpos] == '*')
				{
                    bkt = false;
                    while (line[jpos] != '\0' || !stream.atEnd() )
					{
						a = line[jpos];
                        if (a == '\0' || line.empty())
						{
                            line.clear();
                            line = (string)stream.readLine().toUtf8().constData();
                            TransformTab(line);
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
                                if (a != '\0' /*&& !stream.atEnd()*/)
								{
									goto start;
                                }
								jpos--;
                                bkt = true;
								break;
							}
                            else
                            {
                                jpos--;/*
                                         данный костыль для того,
                                         чтобы не перескакивать через
                                         один символ при считывании коммента
                                       */
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
                    All.Data.AddTail(elem.c_str(), (int)a, ipos+1, /*jpos-1*/jpos);
					a = line[jpos];
                    //goto start;
                    jpos--;
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

void Lexical::TransformTab(string &line)
{
    //костыль для того, чтобы считать
    //нормально позицию элемента при вводе
    //символа табуляции
    int t_pos = line.find('\t');

    if (t_pos != -1)
    {
        line.erase(t_pos,1);
        line.insert(t_pos,"                    ");
    }
}
