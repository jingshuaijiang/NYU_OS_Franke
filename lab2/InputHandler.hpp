//
//  InputHandler.hpp
//  Lab2
//
//  Created by jjs on 2020/3/25.
//  Copyright © 2020 jjs.cn. All rights reserved.
//

#ifndef InputHandler_hpp
#define InputHandler_hpp

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string>
#include "Scheduler.hpp"
using namespace std;

class InputHandler
{
public:
    int ofs=0;
    int verbose=0;
    int preprio = 0;
    int quantum=10000;
    int maxprio = 4;
    string type;
    int LINE_LENGTH = 1000;
    int* randvals;
    char* linearray;
    int myrandom(int burst);
    void Read_Random_File(ifstream & randomfile);
    void Read_Input_File(ifstream& inputfile, deque<Process*>* ProcessList);
    Scheduler* argmentParse(int argc, char** argv);
};


#endif /* InputHandler_hpp */
