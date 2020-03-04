//
//  Errorhandler.hpp
//  Lab1
//
//  Created by jjs on 2020/2/21.
//  Copyright © 2020 jjs.cn. All rights reserved.
//

#ifndef Errorhandler_hpp
#define Errorhandler_hpp

#include <stdio.h>
#include "Table.hpp"
#include <string>
#include <fstream>
#include <iostream>


using namespace std;

class Errorhandler {
public:
    void NumChecker(std::string Token, int lineNum, int lineOffset);
    void SymbolChecker(std::string Token, int lineNum, int lineOffset);
    void IREAChecker(std::string Token, int lineNum, int lineOffset);
    void DefCountChecker(int defcount, int lineNum, int lineOffset);
    void UseCountChecker(int usecount, int lineNum, int lineOffset);
    void InstCountChecker(int instcount, int lineNum, int lineOffset);
    void Rule5Checker(Table symboltable, int moduleoffset, int module, int instcount);
    string Rule10Checker(int operand);
    string Rule11Checker(int operand);
    string Rule8Checker(int operand);
    string Rule9Checker(int operand, int length);
    string Rule6Checker(int useNum, int tablelength);
    string Rule3Checker(string sym, Table symboltable);
    void Rule7Checker(Table moduletable);
    void Rule4Checker(Table symboltable);
    void Parseerror(int errcode, int line, int lineOffset);
};

#endif /* Errorhandler_hpp */

