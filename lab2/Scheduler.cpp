//
//  Scheduler.cpp
//  Lab2
//
//  Created by jjs on 2020/3/25.
//  Copyright © 2020 jjs.cn. All rights reserved.
//

#include "Scheduler.hpp"
//FCFS: First come First serverd algorithm

void FCFS_Scheduler::add_Process(Process* pro)
{
    runQueue.push_back(pro);
    return;
}

Process* FCFS_Scheduler::get_next_Process()
{
    if (runQueue.size() == 0)
        return NULL;
    Process* curr = runQueue.front();
    runQueue.pop_front();
    return curr;
}

// LCFS: Last come First servered algorithm
void LCFS_Scheduler::add_Process(Process* pro)
{
    runQueue.push_front(pro);
    return;
}


Process* LCFS_Scheduler::get_next_Process()
{
    if (runQueue.size() == 0)
        return NULL;
    Process* curr = runQueue.front();
    runQueue.pop_front();
    return curr;
}

//SRTF shortest remaining time first.
void SRTF_Scheduler::add_Process(Process* pro)
{
    if (runQueue.size() == 0)
        runQueue.push_front(pro);
    else
    {
        int remain_time = pro->RC;
        int i = 0;
        for (i; i < runQueue.size(); i++)
        {
            if (runQueue.at(i)->RC > remain_time)
                break;
        }
        std::deque<Process*>::iterator it = runQueue.begin() + i;
        runQueue.insert(it, pro);
    }
    return;
}

Process* SRTF_Scheduler::get_next_Process()
{
    if (runQueue.size() == 0)
        return NULL;
    Process* curr = runQueue.front();
    runQueue.pop_front();
    return curr;
}
//Round robin algorithm
void RR_Scheduler::add_Process(Process* pro)
{
    if (pro->dynamic_Prio == -1)
    {
        pro->dynamic_Prio = pro->static_Prio - 1;
    }
    runQueue.push_back(pro);
    return;
}

Process* RR_Scheduler::get_next_Process()
{
    if (runQueue.size() == 0)
        return NULL;
    Process* curr = runQueue.front();
    runQueue.pop_front();
    return curr;
}
//
void PRIO_Scheduler::add_Process(Process* pro)
{
    if (pro->dynamic_Prio == -1)
    {
        pro->dynamic_Prio = pro->static_Prio - 1;
        expiredQ[pro->dynamic_Prio].push_back(pro);
        return;
    }
    activeQ[pro->dynamic_Prio].push_back(pro);
    return;
}

Process* PRIO_Scheduler::get_next_Process()
{
    if (Empty(activeQ) && Empty(expiredQ))
        return NULL;
    if (Empty(activeQ))
    {
        for (int i = 0; i < max; i++)
        {
            int size = expiredQ[i].size();
            for (int j = 0; j < size; j++)
            {
                activeQ[i].push_back(expiredQ[i].front());
                expiredQ[i].pop_front();
            }
        }
    }
    int index = max-1;
    for (index; index >= 0; index--)
    {
        if (activeQ[index].size() == 0)
            continue;
        else
        {
            break;
        }
    }
    Process* curr = activeQ[index].front();
    activeQ[index].pop_front();
    return curr;
}

bool PRIO_Scheduler::Empty(deque<Process*> *runqueue)
{
    for (int i = 0; i < max; i++)
    {
        if (runqueue[i].size() != 0)
        {
            return false;
        }
    }
    return true;
}
