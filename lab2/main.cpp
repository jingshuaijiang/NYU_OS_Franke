//
//  main.cpp
//  Lab2
//
//  Created by jjs on 2020/3/25.
//  Copyright © 2020 jjs.cn. All rights reserved.
//

#include <iostream>

// Lab2_Scheduler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "EventHandler.hpp"
#include <iostream>
#include "Event.hpp"
#include <stdio.h>
#include <queue>
#include <iostream>
#include <fstream>
#include "Scheduler.hpp"
#include "InputHandler.hpp"
#include "Output.hpp"


using namespace std;
int Finish_Time = 0;
int IO_Time = 0;
Output out;
deque<Process*> processQueue;
EventHandler eh;
InputHandler ih;

void Simulation(Scheduler* s) {
    Event* evt;
    event_transition Next_Transition;
    Process* CURRENT_RUNNING_PROCESS = NULL;
    bool CALL_SCHEDULER = false;
    int CURRENT_TIME = 0;
    int CURRENT_BLOCK_TIME = 0;
    while ((evt = eh.get_event())) {
        Process* proc = evt->p; // this is the process the event works on
        CURRENT_TIME = evt->timestamp;
        
        proc->timeInPrevState = CURRENT_TIME - proc->state_ts;
        switch (evt->transition) { // which state to transition to?
        case TRANS_TO_READY:
        {
            int flag1 = 0;
            int flag2 = 0;
            proc->state_ts = CURRENT_TIME;
            // must come from BLOCKED or from PREEMPTION
            // must add to run queue
            out.Trace_Ready(proc, CURRENT_TIME, ih.verbose, flag1, flag2);
            if (CURRENT_RUNNING_PROCESS != NULL)
            {
                if (ih.preprio == 1 && proc->dynamic_Prio > CURRENT_RUNNING_PROCESS->dynamic_Prio)
                {
                    flag1 = 1;
                    if (CURRENT_RUNNING_PROCESS->nexttime - CURRENT_TIME > 0)
                    {
                        flag2 = 1;
                        eh.remove_event(CURRENT_RUNNING_PROCESS);
                        CURRENT_RUNNING_PROCESS->RC = CURRENT_RUNNING_PROCESS->RC + CURRENT_RUNNING_PROCESS->nexttime - CURRENT_TIME;
                        CURRENT_RUNNING_PROCESS->remaining_CB = CURRENT_RUNNING_PROCESS->remaining_CB + CURRENT_RUNNING_PROCESS->nexttime - CURRENT_TIME;
                        out.Trace_Pre(proc, CURRENT_RUNNING_PROCESS, CURRENT_TIME, ih.verbose, flag1, flag2);
                        CURRENT_RUNNING_PROCESS->nexttime = CURRENT_TIME;
                        Event* e = new Event(CURRENT_RUNNING_PROCESS, CURRENT_TIME, TRANS_TO_PREEMPT);
                        eh.put_event(e);
                        
                    }
                    else
                    {
                        out.Trace_Pre(proc, CURRENT_RUNNING_PROCESS, CURRENT_TIME, ih.verbose, flag1, flag2);
                    }
                }
                else
                {
                    if (ih.preprio == 1)
                    {
                        out.Trace_Pre(proc, CURRENT_RUNNING_PROCESS, CURRENT_TIME, ih.verbose, flag1, flag2);

                    }
                }
            }
            //CURRENT_RUNNING_PROCESS = nullptr;
            s->add_Process(proc);
            
            CALL_SCHEDULER = true; // conditional on whether something is run
            break;
        }

        case TRANS_TO_RUN:
        {
            int runtime = 0;
            CURRENT_RUNNING_PROCESS = proc;
            proc->CW += proc->timeInPrevState;
            proc->state_ts = CURRENT_TIME;
            // if we do not have a remaining CPU burst then we generate one.
            if (proc->remaining_CB == 0)
            {
                proc->remaining_CB = ih.myrandom(proc->CB);
                proc->generated_CB = proc->remaining_CB;
                ih.ofs++;
            }
            // if the remaining cpu burst in this time is less than or equal to the quantum
            // then the next time is block
            if (proc->remaining_CB > proc->RC)
            {
                proc->remaining_CB = proc->RC;
            }
            if (proc->remaining_CB <= ih.quantum)
            {
                Next_Transition = TRANS_TO_BLOCK;
                runtime = proc->remaining_CB;
                proc->remaining_CB = 0;
            }
            //else which means the quantum of this process is all used, then it needs to be preempt.
            else
            {
                Next_Transition = TRANS_TO_PREEMPT;
                runtime = ih.quantum;
                proc->remaining_CB -= ih.quantum;
            }
            if (proc->RC - runtime < 0)
            {
                runtime = proc->RC;
            }
            // remaining cpu time should be adjusted
            proc->RC -= runtime;
            proc->nexttime = CURRENT_TIME + runtime;
            proc->state = STATE_RUNNING;
            out.Trace_Run(proc, CURRENT_TIME, ih.verbose,runtime);
            Event* e = new Event(proc, CURRENT_TIME + runtime, Next_Transition);
            eh.put_event(e);
            break;
        }

        case TRANS_TO_BLOCK:
        {
            proc->state_ts = CURRENT_TIME;
            // if the remaining cpu time is 0 which means it is already done. Then we write done the finisth time and do nothing about I/O
            if (proc->RC <= 0)
            {
                proc->RC = 0;
                proc->FT = CURRENT_TIME;
                out.Trace_Done(proc, proc->FT, ih.verbose);
            }
            // which means the process needs I/O
            else
            {
                int blocktime = ih.myrandom(proc->IO);
                ih.ofs++;
                proc->state = STATE_BLOCKED;
                proc->IT += blocktime;
                proc->dynamic_Prio = proc->static_Prio - 1;
                Event* e = new Event(proc, CURRENT_TIME + blocktime, TRANS_TO_READY);
                eh.put_event(e);
                if (CURRENT_TIME < CURRENT_BLOCK_TIME) {
                    if (CURRENT_TIME + blocktime > CURRENT_BLOCK_TIME) {
                        IO_Time = IO_Time + CURRENT_TIME + blocktime - CURRENT_BLOCK_TIME;
                        CURRENT_BLOCK_TIME = CURRENT_TIME + blocktime;
                    }
                }
                else {
                    IO_Time = IO_Time + blocktime;
                    CURRENT_BLOCK_TIME = CURRENT_TIME + blocktime;
                }
                out.Trace_Block(proc, CURRENT_TIME, ih.verbose, IO_Time,blocktime);
            }
            CURRENT_RUNNING_PROCESS = nullptr;
            CALL_SCHEDULER = true;
            break;
        }

        case TRANS_TO_PREEMPT:
        {
            CURRENT_RUNNING_PROCESS = NULL;
            proc->dynamic_Prio -= 1;
            if (ih.preprio == 2)
            {
                proc->dynamic_Prio += 1;
            }
            
            proc->state_ts = CURRENT_TIME;
            out.Trace_Preempt(proc, proc->state_ts, ih.verbose, ih.type);
            s->add_Process(proc);
            
            // add to runqueue (no event is generated)
            CALL_SCHEDULER = true;
            break;
        }

        }
        // remove current event object from Memory
        delete evt; evt = nullptr;
        if (CALL_SCHEDULER) {
            if (eh.get_next_event_time() == CURRENT_TIME)
                continue; //process next event from Event queue
            CALL_SCHEDULER = false; // reset global flag
            if (CURRENT_RUNNING_PROCESS == nullptr) {
                CURRENT_RUNNING_PROCESS = s->get_next_Process();
                if (CURRENT_RUNNING_PROCESS == nullptr)
                    continue;
                Event* e = new Event(CURRENT_RUNNING_PROCESS, CURRENT_TIME, TRANS_TO_RUN);
                eh.put_event(e);
                // create event to make this process runnable for same time.
            }
        }
    }
    Finish_Time = CURRENT_TIME;
}

int main(int argc, char** argv)
{
    int c;
    ifstream input(argv[argc-2]);
    ifstream random(argv[argc-1]);
    Scheduler* s = ih.argmentParse(argc, argv);
    ih.Read_Random_File(random);
    ih.Read_Input_File(input, &processQueue);
    eh.Initiliaze_Event_Queue(processQueue);
    Simulation(s);
    out.print(processQueue, Finish_Time, IO_Time,ih.type);
}



    






