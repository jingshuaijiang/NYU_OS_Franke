//
//  Output.hpp
//  Lab2
//
//  Created by jjs on 2020/3/25.
//  Copyright © 2020 jjs.cn. All rights reserved.
//

#ifndef Output_hpp
#define Output_hpp

#include <stdio.h>
#include "Process.hpp"
#include <deque>
#include <string>
#include <iostream>
using namespace std;
class Output
{
public:
    void print(deque<Process*> Process_List, int Finish_Time, int IO_Time, string type);
    void Trace_Ready(Process* p, int timestamp, int verbose,int flag1,int flag2);
    void Trace_Run(Process* p, int timestamp, int verbose, int runtime);
    void Trace_Block(Process* p, int timestamp, int verbose,int IO_Time, int blocktime);
    void Trace_Preempt(Process* p, int timestamp, int verbose,string type);
    void Trace_Done(Process* p, int timestamp, int verbose);
    void Trace_Pre(Process* p, Process* curr, int timestamp, int verbose, int flag1, int flag2);
};


#endif /* Output_hpp */
