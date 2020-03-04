//
//  Table.hpp
//  Lab1
//
//  Created by jjs on 2020/2/25.
//  Copyright © 2020 jjs.cn. All rights reserved.
//

#ifndef Table_hpp
#define Table_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

struct Symbol {
    string sym;
    int val;
    int definedmodulenum = -1;
    string warninfo;
    Symbol* next;
    int moduleOffset;
    int globaluse=0;
    int localuse=-1;
};


class Table
{

public:
    Symbol* head;
    Symbol* GetNode(string usesym);
    void AddAtHead(string sym, int val, int moduleoffset,int definedmodulenum);
    void AddAtTail(string sym, int val,int moduleoffset,int definedmodulenum);
    void AddAtHead(string sym, int moduleoffset, int definedodulenum);
    void AddAtTail(string sym, int moduleoffset, int definedmodulenum);
    int GetTableLength();
    int Finds(string sym);
    void AddWarningInfo(string sym);
    void MarkSymUse(string sym);
    void MarkModuleUse(string sym);
    void PrintNonuselist();
    void PrintNonActualUsedlist();
    void Free();

};

#endif /* Table_hpp */
