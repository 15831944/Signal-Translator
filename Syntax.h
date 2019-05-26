#pragma once
#include "StringList.h"
#include "QFile"
#include "QTextStream"
#include "Lexical.h"
#include <string.h>

using namespace std;
struct leaf;

//vector "tree"
struct leaf
{

public:

    int lexem_id;
    int level;
    string name;
    struct vector<leaf> child;

    leaf()
    {
        level = 0;
        lexem_id = 0;
        name = "";
    };
    leaf(int level_number, int leaf_id, string node_name)
    {
        lexem_id = leaf_id;
        level = level_number;
        name = node_name;
    };

    void delete_last_child()
    {
        if (child.size() > 0)
            child.pop_back();
    };
    void add_child(int leaf_id, int child_id, string name)
    {
        child.push_back(leaf(leaf_id, child_id, name));
    }
    leaf& get_child(int i)
    {
        if (i < child.size() && i >= 0)
            return child[i];
    }
    void print_tree()
    {
        for (int i = 0; i < level - 1; i++)
            cout << "|   ";
            cout << "|-->" << name << endl;
        for (auto &i : child)
            i.print_tree();
    }

    void write_tree()
    {
        QFile file("C:\\Users\\0137\\Desktop\\SignalTranslator\\Resource\\TreeB.txt");

        if (!file.open(QIODevice::WriteOnly))
        {
            cout << "Файл не открыт\n\n";
            file.close();
            return;
        }

        QTextStream Outstream(&file);

        string tree = "";

        tree = write(tree);


        Outstream << tree.c_str();

        file.close();
    }

private:

    string write(string tree)
    {
        for (int i = 0; i < level - 1; i++)
           tree += "|   ";
           tree += "|-->" + name + "\n";
        for (auto &i : child)
            tree = i.write(tree);
        return tree;
    }
};


class Syntax
{
public:
    Syntax(struct All_in_One All);
    ~Syntax(){}

    //for store Tree in text format
    QString Tree;
    leaf tree;

    bool isError()
    {
        return Error;
    }

    const char * GetErrorM()
    {
        return Err.c_str();
    }
private:

    QString Add_Dots();

    void ShowTree();

    QString to_QString(string data);

    //<signal-programm> --> <programm>
    void SyntaxStart(StringList Data);

    //<program> --> PROCEDURE <procedure-identifier><parameters-list>; <block>;
    void Rule2(ListNode *Curr);

    //<block> --> <declarations> BEGIN <statements-list> END
    ListNode* Rule3(ListNode *Curr);

    //<statements-list> --> <empty>
    ListNode* Rule4(ListNode *Curr);

    //<parameters-list> --> ( <declarations-list> ) | <empty>
    ListNode* Rule5(ListNode *Curr);

    //<declarations> --> <variable-declarations>
    ListNode* Rule6(ListNode *Curr);

    //<variable-declarations> --> VAR <declarations-list> | <empty>
    ListNode* Rule7(ListNode *Curr);

    //<declarations-list> --> <declaration> <declarations-list> | <empty>
    ListNode* Rule8(ListNode *Curr);

    //<declaration> --> <variable-identifier><identifiers-list>:<attribute><attributes-list>;
    ListNode* Rule9(ListNode *Curr);

    //<identifiers-list> --> , <variable-identifier> <identifiers-list> | <empty>
    ListNode* Rule10(ListNode *Curr);

    //<attributes-list> --> <attribute> <attributes-list> | <empty>
    ListNode* Rule11(ListNode *Curr);

    //<attribute> --> SIGNAL | COMPLEX | INTEGER | FLOAT | BLOCKFLOAT | EXT
    ListNode* Rule12(ListNode *Curr);

    //<variable-identifier> --> <identifier>
    ListNode* Rule13(ListNode *Curr);

    //<procedure-identifier> --> <identifier>
    ListNode* Rule14(ListNode *Curr);

    //<identifier> --> <letter><string>
    ListNode* Rule15(ListNode *Curr);

    //checking for "BEGIN" and "END"
    void isBeginEnd();




    StringList Data;
    StringList Keywords;
    int Dots;
    bool Error;
    string Err;

    string temporary;
};

