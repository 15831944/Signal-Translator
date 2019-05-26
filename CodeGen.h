#pragma once
#include "StringList.h"
#include "QFile"
#include "QTextStream"
#include "Lexical.h"
#include <string.h>


class CodeGenerator
{
        public:
            CodeGenerator(struct All_in_One All, struct leaf L);
            ~CodeGenerator(){};

            //for store Tree in text format


            bool isError()
            {
                return Error;
            }

            const char * GetErrorM()
            {
                return Err.c_str();
            }

            QString GetASM()
            {
                return ASM;
            }
        private:

            QString to_QString(string data);

            void StartGen(struct All_in_One All);

            void SemanticErr();

            void block(ListNode * curr);

            ListNode * parametersList();

            QString GetElem(int level);

            int get_stack_counter (char *i);

            const char *to_Str(QString elem);

            const char * type(int i);

            QString ASM;

            StringList Data;

            bool Error;
            string Err;

            StringList Identifiers;
            StringList ASM_Keywords;

            leaf Leaf;
            int level;
 };
