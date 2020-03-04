//
//  Filehandler.cpp
//  Lab1
//
//  Created by jjs on 2020/2/21.
//  Copyright © 2020 jjs.cn. All rights reserved.
//


#include "Filehandler.hpp"
#include "Errorhandler.hpp"
#include <string.h>



void Filehandler::MyReadLine(ifstream &fin)
{
    delete[] linearray;
    linearray = new char[LINE_LENGTH];
    fin.getline(linearray, LINE_LENGTH);

    if (linearray[0] == '\0' && fin.eof())
    {
        lineNum++;
        return;
    }
    lineNum++;
    lineOffset = 0;
    bool he =linearray[0] == '\0';
    bool p = !fin.eof();
    while(linearray[0] == '\0' && !fin.eof())
    {
        fin.getline(linearray, LINE_LENGTH);
        lineNum++;
        lineOffset = 0;
    }
}

string Filehandler::getToken(ifstream &fin)
{
    char* pch = NULL;
    char* next_token = NULL;

    //MyReadLine(fin);
    //pch = strtok(linearray, "'\t' '\n'");
    pch = strtok(NULL, " '\t''\n'");
    while (pch==NULL && !fin.eof())
    {
        MyReadLine(fin);
        pch = strtok(linearray,"'\t' '\n'");
    }
    if (pch == NULL && fin.eof())
    {
        return "end of file";
    }
    string TokenString(pch);
    while (linearray[lineOffset] != pch[0]) lineOffset++;
    return TokenString;
}

int Filehandler::readInt(ifstream &fin)
{
    string Token = getToken(fin);
    if (Token == "end of file") return -1;
    ehl.NumChecker(Token,lineNum,lineOffset);

    ResetlineOffset(Token);
    return stoi(Token);
}

string Filehandler::readSymbol(ifstream &fin)
{
    string Token = getToken(fin);
    ehl.SymbolChecker(Token, lineNum, lineOffset);
    ResetlineOffset(Token);
    return Token;
}

string Filehandler::readIAER(ifstream &fin)
{
    string Token = getToken(fin);
    ehl.IREAChecker(Token, lineNum, lineOffset);
    ResetlineOffset(Token);
    return Token;
}

void Filehandler::ResetlineOffset(string Token)
{
    lineOffset = lineOffset + (int)Token.length();
}
