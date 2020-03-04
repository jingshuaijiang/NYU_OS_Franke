// lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "Filehandler.hpp"
#include "Errorhandler.hpp"
#include "Insthandler.hpp"
#include "Table.hpp"
using namespace std;


int main(int argc, const char* argv[])
{
    string fileAddress = string(argv[1]);
    Filehandler filehandler;
    Errorhandler errorhandler;
    Insthandler insthandler;
    Table symboltable;
    Table moduletable;
    int moduleoffset = 0;
    int module = 0;
    //pass1 begins
    ifstream pass1(fileAddress, ifstream::in);
    while (!pass1.eof())
    {
        //module count
        module++;
        //read the define count
        int defcount = filehandler.readInt(pass1);
        //if reached end of file (blank line) break
        if (defcount == -1) break;
        //check if the defcount exceeds 16
        errorhandler.DefCountChecker(defcount,filehandler.lineNum,0);

        //read the symbol and the value
        for (int i = 0; i < defcount; i++) {
            string sym = filehandler.readSymbol(pass1);
            int val = filehandler.readInt(pass1);
            //if multiple defined
            if (symboltable.Finds(sym)==1)
            {
                //print warning information
                symboltable.AddWarningInfo(sym);
            }
            else //add to the symbol table
            {
                symboltable.AddAtTail(sym, val, moduleoffset, module);
            }

        }
        //read the usecount
        int usecount = filehandler.readInt(pass1);
        //check if the usecount exceeds 16
        errorhandler.UseCountChecker(usecount, filehandler.lineNum, 0);

        //read the used symbol
        for (int i = 0; i < usecount; i++) {
            string sym = filehandler.readSymbol(pass1);

        }
        //read the instruction count
        int instcount = filehandler.readInt(pass1);
        moduleoffset = moduleoffset + instcount;
        //check if instruction count exceeds 512
        errorhandler.InstCountChecker(moduleoffset, filehandler.lineNum, 0);
        errorhandler.Rule5Checker(symboltable, moduleoffset, module, instcount);
        for (int i = 0; i < instcount; i++) {

            string addressmode = filehandler.readIAER(pass1);
            int operand = filehandler.readInt(pass1);
        }
    }
//    pass1.ios_base::clear();

    //pass1 finished
    pass1.close();
    
    //output the symbol table
    cout << "Symbol Table" << endl;
    Symbol* current = symboltable.head;
    while (current != NULL)
    {
        string sym = current->sym;
        int outval = current->val +current->moduleOffset;
        cout << sym << "=" <<outval;
        if (!current->warninfo.empty())
        {
            //if there is warning info just output it.
            cout << current->warninfo;
        }
        current = current->next;
        cout << endl;
    }
    cout << endl;
    cout << "Memory Map" << endl;
    
    //reset all the parameters and start a new pass
    moduleoffset = 0;
    module = 0;
;

    //
    //pass2 begins
    //
    pass1.open(fileAddress);
    while (!pass1.eof())
    {

        module++;
        int defcount = filehandler.readInt(pass1);
        if (defcount == -1) break;
       //again read symbol and values but do nothing
        for (int i = 0; i < defcount; i++) {
            string sym = filehandler.readSymbol(pass1);
            int val = filehandler.readInt(pass1);
        }
        //get the used symbol number
        int usecount = filehandler.readInt(pass1);
       //read the used symbols and store them in a table and mark the symbol defined in the definishion list used.
        for (int i = 0; i < usecount; i++) {
            string sym = filehandler.readSymbol(pass1);
            moduletable.AddAtTail(sym, moduleoffset, module);
            symboltable.MarkSymUse(sym);
        }
        //get the instruction number
        int instcount = filehandler.readInt(pass1);
        //read the instruction and the operand and print them according to the rule
        for (int i = 0; i < instcount; i++) {
            string addressmode = filehandler.readIAER(pass1);
            int operand = filehandler.readInt(pass1);
            insthandler.PrintInst(addressmode,operand,symboltable,moduletable,instcount,moduleoffset);
        }
        //offset added
        moduleoffset = moduleoffset + instcount;
        //check actual used symbols and print warning info
        errorhandler.Rule7Checker(moduletable);
        //module used symbol table should be freed after each module is finished.
        moduletable.Free();
    }
    cout<<endl;
    //print the symbol that was defined by not used.
    errorhandler.Rule4Checker(symboltable);

  



}

