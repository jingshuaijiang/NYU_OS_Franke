//
//  Output.cpp
//  Lab2
//
//  Created by jjs on 2020/3/25.
//  Copyright © 2020 jjs.cn. All rights reserved.
//

#include "Output.hpp"


void Output::print(deque<Process*> Process_List,int Finish_Time, int IO_Time,string type)
{
    double Total_Turn = 0;
    double Total_CPUW = 0;
    double Total_CPU_T = 0;
    cout << type << "\n";
    for (int i = 0; i < Process_List.size(); i++)
    {
        Total_Turn += Process_List.at(i)->FT - Process_List.at(i)->AT;
        Total_CPUW += Process_List.at(i)->CW;
        Total_CPU_T += Process_List.at(i)->TC;
        printf("%04d: %4d %4d %4d %4d %1d | %5d %5d %5d %5d\n",
            Process_List.at(i)->pid,
            Process_List.at(i)->AT,
            Process_List.at(i)->TC,
            Process_List.at(i)->CB,
            Process_List.at(i)->IO,
            Process_List.at(i)->static_Prio,
            Process_List.at(i)->FT,
            Process_List.at(i)->FT - Process_List.at(i)->AT,
            Process_List.at(i)->IT,
            Process_List.at(i)->CW);
    }
    double CPU_U = 100 * (double)Total_CPU_T / (double)Finish_Time;
    double IO_U = 100 * (double)IO_Time / (double)Finish_Time;
    double Average_TurnA = (double)Total_Turn / (double)Process_List.size();
    double Average_CPUW = (double)Total_CPUW / (double)Process_List.size();
    double Through_P = (double)Process_List.size() * 100 / (double)Finish_Time;

    printf("SUM: %d %.2lf %.2lf %.2lf %.2lf %.3lf\n", Finish_Time,
        CPU_U,
        IO_U,
        Average_TurnA,
        Average_CPUW,
        Through_P);

}
void Output::Trace_Pre(Process* p, Process* curr,int timestamp, int verbose, int flag1, int flag2)
{
    int i = 0;
    if(p->dynamic_Prio > curr->dynamic_Prio)
    {
        i=1;
    }
    if(verbose==1)
    {
        if (flag2 == 1)
           {
               printf("---> PRIO preemption %d by %d ? %d TS=%d now=%d) --> YES\n",curr->pid,p->pid,i,curr->nexttime,timestamp);
           }
           else
           {
               printf("---> PRIO preemption %d by %d ? %d TS=%d now=%d) --> NO\n", curr->pid, p->pid,  i,curr->nexttime, timestamp);

           }
    }
   
    
}

void Output::Trace_Ready(Process* p, int timestamp, int verbose,int flag1,int flag2)
{
    if (verbose == 1)
    {
        if (flag1 == 0 && flag2 == 0)
        {
            if (p->created == 0)
            {
                printf("%d %d 0: CREATED -> READY\n", timestamp, p->pid);
                p->created = 1;
            }
            else
            {
                printf("%d %d %d: BLOCK -> READY\n", timestamp, p->pid, p->timeInPrevState);
            }
        }
    }
}

void Output::Trace_Run(Process* p, int timestamp,int verbose,int runtime)
{
    if (verbose==1)
    {
        printf("%d %d %d: READY -> RUNNG cb=%d rem=%d prio=%d\n", timestamp, p->pid, p->timeInPrevState,p->remaining_CB+runtime, p->RC+runtime,p->dynamic_Prio);
    }
}

void Output::Trace_Block(Process* p, int timestamp, int verbose,int IO_Time,int blocktime)
{
    if (verbose == 1)
    {
        printf("%d %d %d: RUNNG -> BLOCK  ib=%d rem=%d\n", timestamp, p->pid, p->timeInPrevState,blocktime, p->RC);
    }
}

void Output::Trace_Preempt(Process* p, int timestamp, int verbose, string type)
{
    if (verbose == 1)
    {
        if (type.find("RR")!=type.npos)
        {
            printf("%d %d %d: RUNNG -> READY  cb=%d rem=%d prio=%d\n", timestamp, p->pid, p->timeInPrevState, p->remaining_CB, p->RC, p->dynamic_Prio);
        }

        else
        {
            printf("%d %d %d: RUNNG -> READY  cb=%d rem=%d prio=%d\n", timestamp, p->pid, p->timeInPrevState, p->remaining_CB, p->RC, p->dynamic_Prio+1);

        }
    }
   
}

void Output::Trace_Done(Process* p, int timestamp, int verbose)
{
    if (verbose == 1)
    {
        printf("%d %d %d: Done\n", p->FT, p->pid,p->timeInPrevState);
    }
}
