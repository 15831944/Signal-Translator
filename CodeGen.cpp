#include "CodeGen.h"
#include "stdlib.h"

CodeGenerator::CodeGenerator(struct All_in_One All, struct leaf L)
{
    Error = false;
    ASM_Keywords = All.ASM_Keywords;
    Data = All.Data;
    Leaf = L;
    StartGen(All);
}

void CodeGenerator::StartGen(struct All_in_One All)
{
   Identifiers = All.Identifiers;
   level = 5;
   SemanticErr();
   if (!Error)
   {
       ASM = "CODE SEGMENT:\n" + GetElem(level) + "\nPROC \n PUSH EBP \n MOV EBP, ESP\n";

       block(parametersList());

       ASM += "RET \n" + GetElem(5) +"\nENDP \nCODE ENDS\nEND";
   }
   //return;
}

QString CodeGenerator::GetElem(int level)
{
    string temp_ = Leaf.get_child(level).name;

    if (Leaf.get_child(level).lexem_id < 0)
    {
        temp_ = temp_.erase(Leaf.get_child(level).name.length() - 1, Leaf.get_child(level).name.length() - 1);
    }
    else {
         temp_ = temp_.erase(Leaf.get_child(level).name.length() - 1 - fabs(to_string(Leaf.get_child(level).lexem_id).length() ), Leaf.get_child(level).name.length() - 1);
    }

    QString temp = to_QString(temp_.c_str());
    return temp;
}

QString CodeGenerator::to_QString(string data)
{
    return (QString)(data.c_str());
}

const char * CodeGenerator::to_Str(QString elem)
{
    string temp = elem.toUtf8().constData();
    return temp.c_str();
}

int CodeGenerator::get_stack_counter (char *i)
{
    int temp = atoi(i);
    switch(temp)
    {
    case 1:    //SIGNAL
        temp = 1;
        break;
    case 2:    //COMPLEX
        temp = 8;
        break;
    case 3:     //INTEGER
        temp = 4;
        break;
    case 4:     //FLOAT
        temp = 8;
        break;
    case 5:      //BLOCKFLOAT
        temp = 8;
        break;
    case 6:      //EXT
        temp = 2;
        break;

    }
    return temp;
}

ListNode * CodeGenerator::parametersList()
{
    QString ASM_data = "";
    string Spec;
    QString debug;
    ListNode* curr = (ListNode*) Identifiers.GetHead()->next;
    int stack_counter = 8;
    int id_counter = 0;
    while(strcmp(to_Str(GetElem(level)), ")") != 0)
    {
        debug = GetElem(level);
        if (strcmp(to_Str(GetElem(level)), "<identifier>") == 0)
        {
            id_counter++;
        }
        else if (strcmp(to_Str(GetElem(level)), ";") == 0)
        {
            int temp_id = id_counter;
            char temp_c ;

            if ((int)temp_id > (int)Spec.length())
            {
                Error = true;
                Err = "Semantic Error: Too much identifiers in \"<parameters-list>\" ";
                return nullptr;
            }
            for (id_counter = id_counter; id_counter > 0; id_counter--)
            {
                ASM += ";[EBP+" + to_QString(to_string(stack_counter)) + "] - ";
                ASM += curr->str;
                ASM += "\n";
                temp_c = Spec[temp_id - id_counter];
                stack_counter += get_stack_counter(&temp_c);
                curr = curr->next;
            }

            if ((int)temp_id < (int)Spec.length())
            {
                Error = true;
                Err = "Semantic Error: Too much attributes in \"<parameters-list>\" ";
                return nullptr;
            }
            else
            {
                Spec.clear();
                Spec = "";
            }
        }
        else if (strcmp(to_Str(GetElem(level)), ":") == 0)
        {
            while (strcmp(to_Str(GetElem(level)), ";") != 0)
            {
                debug = GetElem(level);
                if (strcmp(to_Str(GetElem(level)), "SIGNAL") == 0)
                {
                    Spec += to_string(1);
                }
                else if (strcmp(to_Str(GetElem(level)), "COMPLEX") == 0)
                {
                    Spec += to_string(2);
                }
                else if (strcmp(to_Str(GetElem(level)), "INTEGER") == 0)
                {
                    Spec += to_string(3);
                }
                else if (strcmp(to_Str(GetElem(level)), "FLOAT") == 0)
                {
                    Spec += to_string(4);
                }
                else if (strcmp(to_Str(GetElem(level)), "BLOCKFLOAT") == 0)
                {
                    Spec += to_string(5);
                }
                else if (strcmp(to_Str(GetElem(level)), "EXT") == 0)
                {
                    Spec += to_string(6);
                }
                level++;
            }
            continue;
        }
        level++;
    }
    level += 2;
    return curr;
}

const char * CodeGenerator::type(int i)
{
    switch(i)
    {
    case 1:
        return "DB";
    case 2:
        return "DW";
    case 4:
        return "DD";
    case 8:
        return "DQ";
    };
    return "null";
}

void CodeGenerator::SemanticErr()
{
    int lev = level;
    ListNode* temp;

    while(strcmp(to_Str(GetElem(lev)), "END") != 0)
    {
         temp = (ListNode*)ASM_Keywords.Find(to_Str(GetElem(lev)));
         QString a = GetElem(lev);
       if (temp != nullptr)
       {
           Error = true;
           Err = "Semantic Error: wrong name used\"";
           Err += Data.Find(temp->str)->str;
           Err += "\" on pos (" + to_string(Data.Find(temp->str)->ipos);
           Err += "," + to_string(Data.Find(temp->str)->jpos);
           Err += ")";
           return;
       }
       lev++;
    }
}

void CodeGenerator::block(ListNode * curr)
{

    if (curr == nullptr)
    {
        return;
    }
    QString ASM_c = "DATA SEGMENT: \n";
    string Spec;
    QString debug;
    int id_counter = 0;
    while(strcmp(to_Str(GetElem(level)), "BEGIN") != 0)
    {
        debug = GetElem(level);
        if (strcmp(to_Str(GetElem(level)), "<identifier>") == 0)
        {
            id_counter++;
        }
        else if (strcmp(to_Str(GetElem(level)), ";") == 0)
        {
            int temp_id = id_counter;
            char temp_c ;

            if ((int)temp_id > (int)Spec.length())
            {
                Error = true;
                Err = "Semantic Error: Too much identifiers in \"<variable-declarations>\" ";
                return;
            }

            for (id_counter = id_counter; id_counter > 0; id_counter--)
            {
                temp_c = Spec[temp_id - id_counter];
                ASM_c += curr->str;
                ASM_c += "   " + to_QString(type(get_stack_counter(&temp_c))) + "   ? ";
                ASM_c += "\n";
                curr = curr->next;
            }

            if ((int)temp_id < (int)Spec.length())
            {
                Error = true;
                Err = "Semantic Error: Too much attributes in \"<variable-declarations>\"";

                return;
            }
            else {
                Spec.clear();
                Spec = "";
            }
        }
        else if (strcmp(to_Str(GetElem(level)), ":") == 0)
        {
            while (strcmp(to_Str(GetElem(level)), ";") != 0)
            {
                debug = GetElem(level);
                if (strcmp(to_Str(GetElem(level)), "SIGNAL") == 0)
                {
                    Spec += to_string(1);
                }
                else if (strcmp(to_Str(GetElem(level)), "COMPLEX") == 0)
                {
                    Spec += to_string(2);
                }
                else if (strcmp(to_Str(GetElem(level)), "INTEGER") == 0)
                {
                    Spec += to_string(3);
                }
                else if (strcmp(to_Str(GetElem(level)), "FLOAT") == 0)
                {
                    Spec += to_string(4);
                }
                else if (strcmp(to_Str(GetElem(level)), "BLOCKFLOAT") == 0)
                {
                    Spec += to_string(5);
                }
                else if (strcmp(to_Str(GetElem(level)), "EXT") == 0)
                {
                    Spec += to_string(6);
                }
                level++;
            }
            continue;
        }
        level++;
    }
    ASM_c += "DATA ENDS\n";

    ASM = ASM_c + ASM;

}

void CodeGenerator::write_to_file()
{
    QFile file("C:\\Users\\0137\\Desktop\\SignalTranslator\\Resource\\ASM_Code.asm");

    if (!file.open(QIODevice::WriteOnly))
    {
        cout << "Файл не открыт\n\n";
        file.close();
        return;
    }

    QTextStream Outstream(&file);

    Outstream << ASM;

    file.close();
}
