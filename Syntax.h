#pragma once
#include "StringList.h"
#include "QFile"
#include "QTextStream"
#include "Lexical.h"
#include <string.h>

using namespace std;

class Syntax
{
public:
    Syntax(struct All_in_One All);
    ~Syntax(){}

    QString Tree;

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

    //<string> --> <letter><string> | <digit><string> | <empty>
    ListNode* Rule16(ListNode *Curr);

    //<digit> --> 0 | 1 | ... | 9
    ListNode* Rule17(ListNode *Curr);

    //<letter> --> A | B | ... | Z
    ListNode* Rule18(ListNode *Curr);

    StringList Data;
    StringList Keywords;
    int Dots;
    bool Error;
    string Err;
};

