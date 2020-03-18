// Lab2_Scheduler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Event.h"
#include "Scheduler.h"

int main()
{
    std::cout << "Hello World!\n";
    
}
void Simulation() {
    Event* evt;
    while ((evt = get_event())) {
        Process* proc = evt->evtProcess; // this is the process the event works on
        CURRENT_TIME = evt->evtTimeStamp;
        timeInPrevState = CURRENT_TIME �C proc->state_ts;
        switch (evt->transition) { // which state to transition to?
        case TRANS_TO_READY:
            // must come from BLOCKED or from PREEMPTION
            // must add to run queue
            CALL_SCHEDULER = true; // conditional on whether something is run
            break;
        case TRANS_TO_RUN:
            // create event for either preemption or blocking
            break;
        case TRANS_TO_BLOCK:
            //create an event for when process becomes READY again
            CALL_SCHEDULER = true;
            break;
        case TRANS_TO_PREEMPT:
            // add to runqueue (no event is generated)
            CALL_SCHEDULER = true;
            break;
        }
        // remove current event object from Memory
        delete evt; evt = nullptr;
        if (CALL_SCHEDULER) {
            if (get_next_event_time() == CURRENT_TIME)
                continue; //process next event from Event queue
            CALL_SCHEDULER = false; // reset global flag
            if (CURRENT_RUNNING_PROCESS == nullptr) {
                CURRENT_RUNNING_PROCESS = THE_SCHEDULER->get_next_process();
                if (CURRENT_RUNNING_PROCESS == nullptr)
                    continue;
                // create event to make this process runnable for same time.
            }
        }
    }
}


