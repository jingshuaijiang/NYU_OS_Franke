//
//  Errorhandler.cpp
//  Lab1
//
//  Created by jjs on 2020/2/21.
//  Copyright © 2020 jjs.cn. All rights reserved.
//


#include"Errorhandler.hpp"


void Errorhandler::NumChecker(std::string Token, int lineNum, int lineOffset)
{

    if (!isdigit(Token.at(0)))
    {
        Parseerror(0, lineNum, lineOffset);
        exit(0);
    }
}
void Errorhandler::DefCountChecker(int defcount, int lineNum, int lineOffset)
{
    if (defcount > 16) {
        Parseerror(4, lineNum, lineOffset);
        exit(0);
    }
}
void Errorhandler::UseCountChecker(int usecount, int lineNum, int lineOffset)
{
    if (usecount > 16) {
        Parseerror(5, lineNum, lineOffset);
        exit(0);
    }
}
void Errorhandler::InstCountChecker(int moduleoffset, int lineNum, int lineOffset)
{
    if (moduleoffset >= 512)
    {
        Parseerror(6,lineNum,lineOffset);
        exit(0);
    }
}

void Errorhandler::SymbolChecker(std::string Token, int lineNum, int lineOffset)
{

    if ((int)Token.length() > 16)
    {
        Parseerror(3, lineNum, lineOffset);
        exit(0);
    }
    bool a = Token=="end of file";
    if (isdigit(Token.at(0)) )
    {
        Parseerror(1, lineNum, lineOffset);
        exit(0);
    }
    if(Token=="end of file")
    {
        Parseerror(1, lineNum-1, lineOffset);
        exit(0);
    }
}
void Errorhandler::Rule5Checker(Table symboltable, int moduleoffset, int module, int instcount)
{
    Symbol* headrepli = symboltable.head;
    while (headrepli != NULL)
    {
        if (headrepli->val>= instcount && headrepli->definedmodulenum==module)
        {
            cout<< "Warning: Module " << module << ": " << headrepli->sym << " too big " << headrepli->val << " (max=" << instcount - 1 << ") assume zero relative" << endl;
            headrepli->val = 0;
        }
        headrepli = headrepli->next;
    }
}
string Errorhandler::Rule10Checker(int operand)
{
    if (operand >= 10000)
    {
        return " Error: Illegal immediate value; treated as 9999";
    }
    else return "";
}

string Errorhandler::Rule11Checker(int operand)
{
    if (operand / 1000 >= 10)
    {
        return " Error: Illegal opcode; treated as 9999";
    }
    else return "";
}

string Errorhandler::Rule8Checker(int operand)
{
    if (operand % 1000 >= 512)
    {
        return " Error: Absolute address exceeds machine size; zero used";
    }
    else return "";
}
string Errorhandler::Rule9Checker(int operand,int length)
{
    if (operand % 1000 > length)
    {
        return " Error: Relative address exceeds module size; zero used";
    }
    else return "";
}

string Errorhandler::Rule6Checker(int useNum, int tablelength)
{
    if (useNum +1 > tablelength)
    {
        return  " Error: External address exceeds length of uselist; treated as immediate";
    }
    else return "";
}

string Errorhandler::Rule3Checker(string sym, Table symboltable)
{
    if (symboltable.Finds(sym) == -1)
    {
        return " Error: " + sym + " is not defined; zero used";
    }
    else return "";
}

void Errorhandler::IREAChecker(std::string Token,int lineNum,int lineOffset)
{

    if ((Token != "I" && Token != "R" && Token != "E" && Token != "A") && Token != "end of file") {
        Parseerror(2, lineNum, lineOffset);
        exit(0);
    }
    if (Token == "end of file") {
        Parseerror(2, lineNum-1, lineOffset);
        exit(0);
    }
}
void Errorhandler::Rule4Checker(Table symboltable)
{
    symboltable.PrintNonuselist();
}

void Errorhandler::Rule7Checker(Table moduletable)
{
    moduletable.PrintNonActualUsedlist();
}
void Errorhandler::Parseerror(int errcode,int line,int lineOffset) {
    static const char* errstr[] = {
    "NUM_EXPECTED", // Number expect
    "SYM_EXPECTED", // Symbol Expected
    "ADDR_EXPECTED", // Addressing Expected which is A/E/I/R
    "SYM_TOO_LONG", // Symbol Name is too long
    "TOO_MANY_DEF_IN_MODULE", // > 16
    "TOO_MANY_USE_IN_MODULE", // > 16
    "TOO_MANY_INSTR", // total num_instr exceeds memory size (512)
    };
    cout << "Parse Error line " << line << " offset " << lineOffset + 1 << ": "<<errstr[errcode] << endl;
}
