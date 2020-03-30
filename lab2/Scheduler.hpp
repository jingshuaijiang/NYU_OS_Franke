//
//  Scheduler.hpp
//  Lab2
//
//  Created by jjs on 2020/3/25.
//  Copyright © 2020 jjs.cn. All rights reserved.
//

#ifndef Scheduler_hpp
#define Scheduler_hpp


#include <stdio.h>
#include <deque>
#include "Event.hpp"

using namespace std;
//define the Scheduler object. And create interface for them.
class Scheduler
{
public:
    deque<Process*> runQueue;
    virtual void add_Process(Process* pro) { return; };
    virtual Process* get_next_Process() { Process* temp = new Process; return temp; };
};

//First come first served sheduler.
class FCFS_Scheduler :public Scheduler
{
public:
    void add_Process(Process* pro);
    Process* get_next_Process();
};

//Last come first served scheduler.
class LCFS_Scheduler :public Scheduler
{
public:
    void add_Process(Process* pro);
    Process* get_next_Process();
};


//
class SRTF_Scheduler :public Scheduler
{
public:
    void add_Process(Process* pro);
    Process* get_next_Process();
};

class RR_Scheduler :public Scheduler
{
    void add_Process(Process* pro);
    Process* get_next_Process();
};

class PRIO_Scheduler :public Scheduler
{
public:
    int max = 4;
    deque<Process*>* activeQ;
    deque<Process*>* expiredQ;
    void add_Process(Process* pro);
    Process* get_next_Process();
    bool Empty(deque<Process*>* runQueue);

    PRIO_Scheduler(int maxprio)
    {
        activeQ = new deque<Process*>[maxprio];
        expiredQ = new deque<Process*>[maxprio];
        max = maxprio;
    }

};


#endif /* Scheduler_hpp */
