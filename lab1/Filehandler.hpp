//
//  Filehandler.hpp
//  Lab1
//
//  Created by jjs on 2020/2/21.
//  Copyright © 2020 jjs.cn. All rights reserved.
//

#ifndef Filehandler_hpp
#define Filehandler_hpp

#include <stdio.h>

#endif /* Filehandler_hpp */

#include <string>
#include <fstream>
#include <iostream>
#include "Errorhandler.hpp"


using namespace std;

class Filehandler
{
public:
    const int LINE_LENGTH = 2000;
    int lineNum=0;
    int lineOffset=0;
    char* linearray;
    Errorhandler ehl;
    Filehandler(){linearray = new char[LINE_LENGTH];};
    void MyReadLine(ifstream& fin);


    string getToken(ifstream& fin);


    int readInt(ifstream& fin);
    string readSymbol(ifstream& fin);
    string readIAER(ifstream& fin);

    void ResetlineOffset(std::string Token);

};

