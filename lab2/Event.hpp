//
//  Event.hpp
//  Lab2
//
//  Created by jjs on 2020/3/25.
//  Copyright © 2020 jjs.cn. All rights reserved.
//

#ifndef Event_hpp
#define Event_hpp

#include <stdio.h>
#include <string.h>
#include "Process.hpp"


typedef enum { TRANS_TO_READY, TRANS_TO_RUN, TRANS_TO_BLOCK, TRANS_TO_PREEMPT, TRANS_TO_DONE } event_transition;
class Event
{
public:
    Process* p;
    int timestamp;
    event_transition transition;

    Event(Process* process, int ts, event_transition et) {
        p = process;
        timestamp = ts;
        transition = et;
    }
};


#endif /* Event_hpp */
