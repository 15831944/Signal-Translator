#include "Syntax.h"
#include "mainwindow.h"

Syntax::Syntax(struct All_in_One All)
{
    Data = All.Data;
    Keywords = All.Keywords;
    Dots = 0;
    Error = false;
    SyntaxStart(Data);
}

QString Syntax::to_QString(string data)
{
    return (QString)(data.c_str());
}

void Syntax::isBeginEnd()
{
    if (Data.Find("BEGIN") == nullptr)
    {
        Error = true;
        Err = "Syntax Error: Missed \"BEGIN\" ";
    }
    else if (Data.Find("END") == nullptr)
    {
        Error = true;
        Err = "Syntax Error: Missed \"END\" ";
    }
}

QString Syntax::Add_Dots()
{
    QString temp = "*";
    for (int i = 0; i < Dots; i++)
    {
        temp += "*";
    }
    return temp;
}

void Syntax::SyntaxStart(StringList Data)
{
    Tree = Add_Dots() + "<signal-program>\n";
    tree.add_child(Dots + 1, -1, "<signal-program>");
    Dots++;
    Tree += Add_Dots() + "<program>\n";
    tree.add_child(Dots + 1, -1, "<program>");
    isBeginEnd();
    if (!Error)
    Rule2((ListNode*) Data.GetHead());

    QFile file("C:\\Users\\0137\\Desktop\\SignalTranslator\\Resource\\Tree.txt");

    if (!file.open(QIODevice::WriteOnly))
    {
        cout << "Файл не открыт\n\n";
        file.close();
        return;
    }

    QTextStream Outstream(&file);

    Outstream << Tree;

    file.close();

    tree.print_tree();

    tree.write_tree();

}

void Syntax::Rule2(ListNode *Curr)
{
    if (strcmp((const char *)Curr->str, "PROCEDURE") == 0)
    {
        Dots++;
        temporary = Curr->str;
        temporary += " " + to_string(Curr->id);
        tree.add_child(Dots + 1, Curr->id, temporary);
        Tree += Add_Dots() + "PROCEDURE " + to_QString(to_string(Curr->id)) + "\n";
        Dots--;
    }
    else
    {
        Error = true;
        Err = "Syntax Error: \"PROCEDURE\" didn't find";
        return;
    }
    Curr = Rule14(Curr->next);
    if (!Error)
    {
        Curr = Rule5(Curr->next);
        if (strcmp((const char*) Curr->str, ")") == 0 && strcmp((const char*) Curr->next->str, ";") != 0)
        {
            Error = true;
            Err = "Syntax Error: Missing \";\" after \")\" on pos (" + to_string(Curr->ipos) + "," + to_string(Curr->jpos) + ")";
        }
        if (strcmp((const char*) Curr->str, ";") != 0)
        {
            Curr = Curr->next;
        }

        if(!Error)
        {
            if (strcmp((const char*) Curr->str, ";") == 0)
            {
                Dots++;
                temporary = Curr->str;
                temporary += " " + to_string(Curr->id);
                tree.add_child(Dots + 1, Curr->id, temporary);
                Tree += Add_Dots() + " ; 59\n";
                Dots--;
            }
        }
    }
    else
    {
        return;
    }

    if (!Error)
    {
        Curr = Rule3(Curr->next);

        if (Curr->next == nullptr && !Error)
        {
            Error = true;
            Err = "Syntax Error: Missing \";\" after \"END\" !\n Pos (" + to_string(Curr->ipos ) + "," + to_string(Curr->jpos + strlen(Curr->str)) + ")";
            return;
        }
        Curr = Curr->next;
        if (!Error)
        {
            if (strcmp ((const char*) Curr->str, ";") == 0)
            {
                Dots++;
                temporary = Curr->str;
                temporary += " " + to_string(Curr->id);
                tree.add_child(Dots + 1, Curr->id, temporary);
                Tree += Add_Dots() + " ; " + to_QString(to_string(Curr->id)) + "\n";
                Dots--;
            }
            else
            {
                Error = true;
                Err = "Syntax Error: Missing \";\" !\n Pos (" + to_string(Curr->ipos) + "," + to_string(Curr->jpos) + ")";
                return;
            }

        }
    }


}

ListNode* Syntax::Rule3(ListNode *Curr)
{
    Dots++;
    tree.add_child(Dots + 1, -1, "<block>");
    Tree += Add_Dots() + "<block>\n";

    Curr = Rule6(Curr);

    if (!Error)
    {
        if (strcmp ((const char*) Curr->str, "BEGIN") == 0)
        {
            Dots++;
            temporary = Curr->str;
            temporary += " " + to_string(Curr->id);
            tree.add_child(Dots + 1, Curr->id, temporary);
            Tree += Add_Dots() + "BEGIN " + to_QString(to_string(Curr->id)) + "\n";
            Dots--;
            Curr = Rule4(Curr->next);

            if (!Error)
            {
                if (strcmp ((const char*) Curr->str, "END") == 0)
                {
                    Dots++;
                    temporary = Curr->str;
                    temporary += " " + to_string(Curr->id);
                    tree.add_child(Dots + 1, Curr->id, temporary);
                    Tree += Add_Dots() + "END " + to_QString(to_string(Curr->id)) + "\n";
                    Dots--;
                }
                else
                {
                    Error = true;
                    Err = "Syntax Error: END doesn't exist !\n Pos (" + to_string(Curr->ipos) + "," + to_string(Curr->jpos) + ")";
                }
            }
        }
        else
        {
            Error = true;
            Err = "Syntax Error: BEGIN doesn't exist !\n Pos (" + to_string(Curr->ipos) + "," + to_string(Curr->jpos) + ")";
        }
    }

    Dots--;
    return Curr;
}

ListNode* Syntax::Rule4(ListNode *Curr)
{
    Dots++;
    tree.add_child(Dots + 1, -1, "<statements-list>");
    Tree += Add_Dots() + "<statements-list>\n";
    Dots++;
    tree.add_child(Dots + 1, -1, "<empty>");
    Tree += Add_Dots() + "<empty>\n";
    if (strcmp ((const char*) Curr->str, "END") != 0)
    {
        Error = true;
        Err = "Syntax Error: <statements-list> must be empty!";
    }
    Dots-= 2;
    return Curr;
}

ListNode* Syntax::Rule5(ListNode *Curr)
{
    Dots++;
    Tree += Add_Dots() + "<parameters-list>\n";
    tree.add_child(Dots + 1, -1, "<parameters-list>");
    if (strcmp((const char*) Curr->str, "(") == 0)
    {
        Dots++;

        temporary = Curr->str;
        temporary += " " + to_string(Curr->id);
        tree.add_child(Dots + 1, Curr->id, temporary);
        Tree += Add_Dots() + " ( 40\n";

        Dots--;
        Curr = Rule8(Curr->next);
        Curr = Curr->next;
        if (!Error)
        {
            if (strcmp((const char*) Curr->str, ")") == 0)
            {
                Dots++;
                temporary = Curr->str;
                temporary += " " + to_string(Curr->id);
                tree.add_child(Dots + 1, Curr->id, temporary);
                Tree += Add_Dots() + " ) 41\n";
                Dots--;
            }
            else
            {
                Error = true;
                Err = "Syntax Error: Missing \";\" on pos (" + to_string(Curr->ipos) + "," + to_string(Curr->jpos) + ")";
            }
        }
    }
    else
    {
        if (strcmp((const char*) Curr->str, ";") == 0)
        {
            Dots++;
            tree.add_child(Dots + 1, -1, "<empty>");
            Tree += Add_Dots() + "<empty>\n";
            Dots--;
        }
        else
        {
            Error = true;
            Err = "Syntax Error: Missing \"(\" on pos (" + to_string(Curr->ipos) + "," + to_string(Curr->jpos) + ")";
        }
    }
    Dots--;
    return Curr;
}

ListNode* Syntax::Rule6(ListNode *Curr)
{
    Dots++;
    tree.add_child(Dots + 1, -1, "<declarations>");
    Tree += Add_Dots() + "<declarations>\n";
    Curr = Rule7(Curr);
    Dots--;
    return Curr;
}

ListNode* Syntax::Rule7(ListNode *Curr)
{
    Dots++;
    tree.add_child(Dots + 1, -1, "<variable-declarations>");
    Tree += Add_Dots() + "<variable-declarations>\n";
    if (strcmp((const char*) Curr->str, "VAR") == 0)
    {
        Dots++;
        temporary = Curr->str;
        temporary += " " + to_string(Curr->id);
        tree.add_child(Dots + 1, Curr->id, temporary);
        Tree += Add_Dots() + "VAR " + to_QString(to_string(Curr->id)) + "\n";
        Dots--;
        Curr = Rule8(Curr->next);
    }
    else if (strcmp((const char*) Curr->str, "BEGIN") == 0)
    {
        Dots++;
        tree.add_child(Dots + 1, Curr->id, "<empty>");
        Tree += Add_Dots() + "<empty>\n";
        Dots--;
    }
    else
    {
        Error = true;
        Err = "Syntax Error: Missed \"VAR\" on pos (" + to_string(Curr->ipos) + "," + to_string(Curr->jpos -1) + ")";
    }
    Dots--;
    return Curr;
}

ListNode* Syntax::Rule8(ListNode *Curr)
{
    Dots++;
    tree.add_child(Dots + 1, -1, "<declarations-list>");
    Tree += Add_Dots() + "<declarations-list>\n";
    if (strcmp((const char*) Curr->str, ")") == 0)
    {
        Dots++;
        tree.add_child(Dots + 1, -1, "<empty>");
        Tree += Add_Dots() + "<empty>\n";
        Dots--;
        Curr = Curr->prev;
    }
    else if (strcmp((const char*) Curr->str, "BEGIN") == 0)
    {
        Dots++;
        tree.add_child(Dots + 1, -1, "<empty>");
        Tree += Add_Dots() + "<empty>\n";
        Dots--;
    }
    else
    {
        Curr = Rule9(Curr);
    }
    Dots--;
    return Curr;
}

ListNode* Syntax::Rule9(ListNode *Curr)
{
    if (strcmp((const char *) Curr->str, ";") == 0 && strcmp((const char *) Curr->prev->str, ";") == 0)
    {
        Error = true;
        Err = "Syntax Error: unnecessary separator \";\" on pos (" + to_string(Curr->ipos) + "," + to_string(Curr->jpos) + ")";
        return Curr;
    }
    else if (strcmp((const char *) Curr->str, ";") == 0)
    {
        Error = true;
        Err = "Syntax Error: Missing \")\" on pos (" + to_string(Curr->ipos) + "," + to_string(Curr->jpos) + ")";
        return Curr;
    }
    Dots++;
    tree.add_child(Dots + 1, -1, "<declaration>");
    Tree += Add_Dots() + "<declaration>\n";
    Curr = Rule13(Curr);
    if (!Error)
    {
        Curr = Rule10(Curr->next);
        if (!Error)
        {
            if (strcmp((const char*) Curr->str, ":") == 0)
            {
                Dots++;
                temporary = Curr->str;
                temporary += " " + to_string(Curr->id);
                tree.add_child(Dots + 1, Curr->id, temporary);
                Tree += Add_Dots() + " : 58\n";
                Dots--;
                Curr = Rule12(Curr->next);

                if (!Error)
                {
                    Curr = Rule11(Curr->next);
                    if (!Error)
                    {
                         if (strcmp((const char*) Curr->str, ";") == 0)
                         {
                             Dots++;
                             temporary = Curr->str;
                             temporary += " " + to_string(Curr->id);
                             tree.add_child(Dots + 1, Curr->id, temporary);
                             Tree += Add_Dots() + " ; 59\n";
                             Dots--;

                             if (strcmp((const char*) Curr->next->str, ")") != 0
                                     && strcmp((const char*) Curr->next->str, "BEGIN") != 0)
                             {

                                  Curr = Rule9(Curr->next);
                             }
                             else if (strcmp((const char*) Curr->next->str, "BEGIN") == 0)
                             {
                                 Curr = Curr->next;
                             }

                         }

                    }
                }
            }
        }
    }

    Dots--;
    return Curr;
}



ListNode* Syntax::Rule10(ListNode *Curr)
{
    Dots++;
    tree.add_child(Dots + 1, -1, "<identifiers-list>");
    Tree += Add_Dots() + "<identifiers-list>\n";

    if (strcmp((const char *)Curr->str, ",") == 0)
    {
        Dots++;
        temporary = Curr->str;
        temporary += " " + to_string(Curr->id);
        tree.add_child(Dots + 1, Curr->id, temporary);
        Tree += Add_Dots() + " , 44\n";
        Curr = Rule13(Curr->next);
        Dots--;
        if (!Error)
        {
            Curr = Rule10(Curr->next);
        }

    }
    else if (strcmp((const char *)Curr->str, ":") == 0)
    {
        //returning;
    }
    else
    {
        Error = true;
        Err = "Syntax Error: wrong <declaration-list> on pos (" + to_string(Curr->ipos) + "," + to_string(Curr->jpos) + ")";
    }
    Dots--;
    return Curr;
}


ListNode* Syntax::Rule11(ListNode *Curr)
{
    if ((strcmp((const char*) Curr->str, ";") != 0) && (strcmp((const char*) Curr->str, "BEGIN") != 0))
    {
        Dots++;
        tree.add_child(Dots + 1, -1, "<attributes-list>");
        Tree += Add_Dots() + "<attributes-list>\n";
        Curr = Rule12(Curr);

        if (!Error)
        {
            Curr = Rule11(Curr->next);
        }

        Dots--;
    }
    if (strcmp((const char*) Curr->str, "BEGIN") == 0)
    {
        Error = true;
        Err = "Syntax Error: Missing \";\" after \"";
        Err += Curr->prev->str;
        Err += "\" on pos (" + to_string(Curr->prev->ipos) + "," + to_string(Curr->prev->jpos + strlen(Curr->prev->str)) + ")";
    }

    return Curr;
}

ListNode* Syntax::Rule12(ListNode *Curr)
{
    if ((strcmp((const char*) Curr->str, ";") == 0) && (strcmp((const char*) Curr->prev->str, ":") == 0))
    {
        Error = true;
        Err = "Syntax Error: Missing attribute after \":\" on pos ("
                + to_string(Curr->ipos) + "," + to_string(Curr->jpos - 1) + ")";
        return Curr;
    }
    else if ((strcmp((const char*) Curr->str, ";") == 0) || (strcmp((const char*) Curr->str, "BEGIN") == 0))
    {
        return Curr;
    }

    Dots++;
    Tree += Add_Dots() + "<atribute>\n";
    tree.add_child(Dots + 1, -1, "<attribute>");
    Dots++;
    if (strcmp((const char*) Curr->str, "SIGNAL") == 0)
    {
        Tree += Add_Dots() + "SIGNAL " + to_QString(to_string(Curr->id)) + "\n";
    }
    else if (strcmp((const char*) Curr->str, "COMPLEX") == 0)
    {
        Tree += Add_Dots() + "COMPLEX " + to_QString(to_string(Curr->id)) + "\n";
    }
    else if (strcmp((const char*) Curr->str, "INTEGER") == 0)
    {
        Tree += Add_Dots() + "INTEGER " + to_QString(to_string(Curr->id)) + "\n";
    }
    else if (strcmp((const char*) Curr->str, "FLOAT") == 0)
    {
        Tree += Add_Dots() + "FLOAT " + to_QString(to_string(Curr->id)) + "\n";
    }
    else if (strcmp((const char*) Curr->str, "BLOCKFLOAT") == 0)
    {
        Tree += Add_Dots() + "BLOCKFLOAT " + to_QString(to_string(Curr->id)) + "\n";
    }
    else if (strcmp((const char*) Curr->str, "EXT") == 0)
    {
        Tree += Add_Dots() + "EXT " + to_QString(to_string(Curr->id)) + "\n";
    }
    else
    {
        Error = true;
        Err = "Syntax Error: Unknown attribute \"";
        Err += Curr->str;
        Err += "\" on pos (" + to_string(Curr->ipos) + "," + to_string(Curr->jpos) + ")";
    }
    temporary = Curr->str;
    temporary += " " + to_string(Curr->id);
    tree.add_child(Dots + 1, Curr->id, temporary);
    Dots-= 2;

    return Curr;
}

ListNode* Syntax::Rule13(ListNode *Curr)
{
    Dots++;
    tree.add_child(Dots + 1, -1, "<variable-identifier>");
    Tree += Add_Dots() + "<variable-identifier>\n";
    Curr = Rule15(Curr);
    Dots--;
    return Curr;
}

ListNode* Syntax::Rule14(ListNode *Curr)
{
    Dots++;
    tree.add_child(Dots + 1, Curr->id, "<procedure-identifier>");
    Tree += Add_Dots() + "<procedure-identifier>\n";

    if ((strcmp((const char*) Curr->next->str, ";") != 0) && (strcmp((const char*) Curr->next->str, "(") != 0))
    {
        Error = true;
        Err =  Err = "Syntax Error: Wrong <procedure-identifier> \"";
        Err += Curr->str;
        Err += "\" on pos (" + to_string(Curr->ipos) + "," + to_string(Curr->jpos) + ")";
        return Curr;
    }
    Curr = Rule15(Curr);
    Dots--;
    return Curr;
}

ListNode* Syntax::Rule15(ListNode *Curr)
{
    Dots++;
    tree.add_child(Dots + 1, -1, "<identifier>");
    Tree += Add_Dots() + "<identifier>\n";
    if (Curr->id > 1000)
    {
        if (Data.Find(Curr->str, Curr) != nullptr)
        {
            Error = true;
            Err = "Syntax Error: Redefinition! \"";
            Err += Curr->str;
            Err += "\" already exist (" + to_string(Curr->ipos) + "," + to_string(Curr->jpos) + ")";
        }
        Dots++;
        temporary = Curr->str;
        temporary += " " + to_string(Curr->id);
        tree.add_child(Dots + 1, Curr->id, temporary);
        Tree += Add_Dots() + to_QString(Curr->str) + " " + to_QString(to_string(Curr->id)) + "\n";
        Dots--;
    }
    else if (Keywords.Find(Curr->str) != nullptr)
    {
        if (strcmp((const char *) Curr->str, Keywords.Find(Curr->str)->str) == 0)
        {
            Error = true;
            Err = "Syntax Error: ";
            Err += Curr->str;
            Err += " is not identifier on pos (" + to_string(Curr->ipos) + "," + to_string(Curr->jpos) + ")";
        }
    }
    else
    {
        Error = true;
        Err = "Syntax Error: Missing identifier after \"";
        Err += Curr->prev->str;
        Err += "\" on pos (" + to_string(Curr->ipos) + "," + to_string(Curr->jpos) + ")";
    }
    Dots--;
    return Curr;
}
