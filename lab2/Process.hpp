//
//  Process.hpp
//  Lab2
//
//  Created by jjs on 2020/3/25.
//  Copyright © 2020 jjs.cn. All rights reserved.
//

#ifndef Process_hpp
#define Process_hpp

#include <stdio.h>
#include <string.h>

typedef enum process_state_t {STATE_CREATED,STATE_READY,STATE_RUNNING, STATE_BLOCKED};

class Process
{
public:
    int pid;//ID of this process
    int AT;//Arrival time
    int TC;//Total CPU time
    int CB;//CPU burst
    int IO;//I/O burst

    int RC;//Rest of CPU time
    int CW;//Cpu waiting time
    int FT;//finish time
    int IT;//I/O time
    int remaining_CB;
    int generated_CB;
    int state_ts;//state time
    int nexttime;

    int created;
    process_state_t state;
    int static_Prio;
    int dynamic_Prio;
    int timeInPrevState;

    Process() {
        IT = 0;
        CW = 0;
        state = STATE_CREATED;
        timeInPrevState = 0;
        remaining_CB = 0;
        static_Prio = 0;
        dynamic_Prio = 0;
        created = 0;
    }
};


#endif /* Process_hpp */
