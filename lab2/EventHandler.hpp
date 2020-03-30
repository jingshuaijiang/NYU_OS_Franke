//
//  EventHandler.hpp
//  Lab2
//
//  Created by jjs on 2020/3/25.
//  Copyright © 2020 jjs.cn. All rights reserved.
//

#ifndef EventHandler_hpp
#define EventHandler_hpp

#include <stdio.h>
#include "Event.hpp"
#include <deque>
using namespace std;
class EventHandler
{
public:
    deque<Event*> Eventqueue;
    void Initiliaze_Event_Queue(deque<Process*> ProcessList);
    Event* get_event();
    void put_event(Event* e);
    int get_next_event_time();
    void remove_event(Process* pro);


};


#endif /* EventHandler_hpp */
