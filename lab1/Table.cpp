//
//  Table.cpp
//  Lab1
//
//  Created by jjs on 2020/2/25.
//  Copyright © 2020 jjs.cn. All rights reserved.
//

#include "Table.hpp"

void Table::AddAtHead(string sym, int val,int moduleoffset,int definedmodulenum)//head can be NULL
{
    Symbol* newsymbol = new Symbol;
    newsymbol->val = val;
    newsymbol->sym = sym;
    newsymbol->definedmodulenum = definedmodulenum;
    newsymbol->moduleOffset = moduleoffset;
    newsymbol->next = head;
    
    head = newsymbol;
}
void Table::AddAtTail(string sym, int val,int moduleoffset,int definedmodulenum)
{
    Symbol* newsymbol = new Symbol;
    newsymbol->val = val;
    newsymbol->sym = sym;
    newsymbol->definedmodulenum = definedmodulenum;
    newsymbol->moduleOffset = moduleoffset;
    newsymbol->next = NULL;
    Symbol* headrepli = head;
    if(headrepli==NULL) head = newsymbol;
    else{
        while(headrepli->next!=NULL)
        {
            headrepli = headrepli->next;
        }
        headrepli->next = newsymbol;
    }
}
void Table::AddAtHead(string sym, int moduleoffset, int definedmodulenum)//head can be NULL
{
    Symbol* newsymbol = new Symbol;
    newsymbol->sym = sym;
    newsymbol->definedmodulenum = definedmodulenum;
    newsymbol->moduleOffset = moduleoffset;
    newsymbol->next = head;

    head = newsymbol;
}

void Table::AddAtTail(string sym, int moduleoffset, int definedmodulenum)//head can be NULL
{
    Symbol* newsymbol = new Symbol;
    newsymbol->sym = sym;
    newsymbol->definedmodulenum = definedmodulenum;
    newsymbol->moduleOffset = moduleoffset;
    newsymbol->next = NULL;
    Symbol* headrepli = head;
    if(headrepli==NULL) head = newsymbol;
    else{
        while(headrepli->next!=NULL)
        {
            headrepli = headrepli->next;
        }
        headrepli->next = newsymbol;
    }
//    head = newsymbol;
}
Symbol* Table::GetNode(string usesym) {
    Symbol* headrepli = head;
    while (headrepli != NULL)
    {
        if (headrepli->sym == usesym)
        {
            break;
        }
        headrepli = headrepli->next;
    }
    return headrepli;
}
int Table::GetTableLength()
{
    int count = 0;
    Symbol* headrepli = head;
    while (headrepli != NULL)
    {
        count++;
        headrepli = headrepli->next;
    }
    return count;
}

int Table::Finds(string sym)
{
    Symbol* headrepli = head;
    while (headrepli != NULL)
    {
        if (headrepli->sym == sym)
        {
            return 1;
        }
        else
        {
            headrepli = headrepli->next;
        }
    }
    return -1;
}
void Table::AddWarningInfo(string sym)
{
    Symbol* current = head;
    while (current != NULL)
    {
        if (current->sym == sym)
        {
            current->warninfo = " Error: This variable is multiple times defined; first value used";
            break;
        }
        else
        {
            current = current->next;
        }
    }

}
void Table::MarkSymUse(string sym)
{
    Symbol* current = head;
    while (current != NULL)
    {
        if (current->sym == sym)
        {
            current->globaluse = 1;
            break;
        }
        else
        {
            current = current->next;
        }
    }
}

void Table::MarkModuleUse(string sym)
{
    Symbol* current = head;
    while (current != NULL)
    {
        if (current->sym == sym)
        {
            current-> localuse= 1;
            break;
        }
        else
        {
            current = current->next;
        }
    }
}

void Table::PrintNonuselist()
{
    Symbol* current = head;
    while (current != NULL)
    {
        if (current->globaluse == 0)
        {
            cout << "Warning: Module " << current->definedmodulenum << ": " << current->sym << " was defined but never used" << endl;
        }

        current = current->next;
        
    }
}

void Table::PrintNonActualUsedlist()
{
    Symbol* current = head;
    while (current != NULL)
    {
        if (current->localuse == -1)
        {
            cout << "Warning: Module " << current->definedmodulenum << ": " << current->sym << " appeared in the uselist but was not actually used" << endl;
        }

        current = current->next;
        
    }
}
void Table::Free()
{
    head =NULL;
}
