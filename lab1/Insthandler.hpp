//
//  Insthandler.hpp
//  Lab1
//
//  Created by jjs on 2020/2/25.
//  Copyright © 2020 jjs.cn. All rights reserved.
//

#ifndef Insthandler_hpp
#define Insthandler_hpp

#include <iostream>
#include <stdio.h>

#include "Errorhandler.hpp"
#include "Table.hpp"

using namespace std;
class Insthandler
{
public:
    string Info = "";
    int printcount = 0;
    Errorhandler ehl;
    void PrintInst(string addressmode, int operand, Table symboltable,Table moduletable,int instcount,int moduleoffset);
    void Ihandler(string addressmode, int operand, Table symboltable);
    void Rhandler(string addressmode, int operand, Table symboltable,int instcount,int moduleoffset);
    void Ehandler(string addressmode, int operand, Table symboltable, Table moduletable);
    string GetUseSym(int useNum, Table moduletable);
    void Ahandler(string addressmode, int operand, Table symboltable);
    void FinalPrint(int operand, string Info);
};

#endif /* Insthandler_hpp */
