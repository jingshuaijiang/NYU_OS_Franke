//
//  Insthandler.cpp
//  Lab1
//
//  Created by jjs on 2020/2/25.
//  Copyright © 2020 jjs.cn. All rights reserved.
//

#include "Insthandler.hpp"


void Insthandler::PrintInst(string addressmode, int operand, Table symboltable, Table moduletable,int instcount, int moduleoffset)
{
    if (addressmode == "I")
    {
        Ihandler( addressmode, operand,  symboltable);
    }
    else if (addressmode == "R")
    {
        Rhandler( addressmode,  operand,  symboltable,instcount,moduleoffset);
    }
    else if (addressmode == "E")
    {
        Ehandler( addressmode,  operand,  symboltable,moduletable);
    }
    else if (addressmode == "A")
    {
        Ahandler( addressmode,  operand,  symboltable);
    }
}
void Insthandler::Ihandler(string addressmode, int operand, Table symboltable)
{
    Info = ehl.Rule10Checker(operand);
    if (Info != "")
    {
        operand = 9999;
    }
    FinalPrint(operand, Info);
}
void Insthandler::Rhandler(string addressmode, int operand, Table symboltable,int instcount,int moduleoffset)
{
    Info = ehl.Rule11Checker(operand);
    if (Info != "")
    {
        operand = 9999;
        FinalPrint(operand,Info);
        return;
    }
    Info = ehl.Rule9Checker(operand, instcount);
    if (Info != "")
    {
        operand = operand - (operand%1000);
    }
    operand = operand + moduleoffset;
    FinalPrint(operand, Info);
}

void Insthandler::Ehandler(string addressmode, int operand, Table symboltable,Table moduletable)
{
    Info = ehl.Rule11Checker(operand);
    if (Info != "")
    {
        operand = 9999;
        FinalPrint(operand, Info);
        return;
    }
    int useNum = operand % 1000;
    Info = ehl.Rule6Checker(useNum, moduletable.GetTableLength());
    if (Info != "")
    {
        FinalPrint(operand, Info);
        return;
    }
    string usesym = GetUseSym(useNum, moduletable);
    Info = ehl.Rule3Checker(usesym, symboltable);
    if (Info != "")
    {
        moduletable.MarkModuleUse(usesym);
        FinalPrint(operand - useNum, Info);
        return;
    }
    Symbol* usesymnode = symboltable.GetNode(usesym);
    moduletable.MarkModuleUse(usesym);
    FinalPrint(operand-useNum + usesymnode->moduleOffset+usesymnode->val, Info);
    return;
}


string Insthandler::GetUseSym(int useNum, Table moduletable)
{
    Symbol* current = moduletable.head;
    while (useNum != 0 && current != NULL)
    {
        current = current->next;
        useNum--;
    }
    return current->sym;
}
void Insthandler::Ahandler(string addressmode, int operand, Table symboltable)
{
    Info = ehl.Rule11Checker(operand);
    if (Info != "")
    {
        operand = 9999;
        FinalPrint(operand, Info);
    }
    Info = ehl.Rule8Checker(operand);
    if (Info != "")
    {
        operand = operand - operand % 1000;
    }
    FinalPrint(operand, Info);
}

void Insthandler::FinalPrint(int operand,string Info)
{
    string counter = "";
    if (printcount < 10)
    {
        counter = "00";
    }
    else if (10 <= printcount && printcount< 100)
    {
        counter = "0";
    }
    if (operand < 10)
        cout << counter << printcount << ": " << "000" << operand << Info << endl;
    else if (operand < 100)
        cout << counter << printcount << ": " << "00" << operand << Info << endl;
    else if (operand < 1000)
        cout << counter << printcount << ": " << "0" << operand << Info << endl;
    else
        cout << counter << printcount << ": " << operand << Info << endl;
    printcount++;
    Info = "";
}
