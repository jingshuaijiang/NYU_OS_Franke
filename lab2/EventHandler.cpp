//
//  EventHandler.cpp
//  Lab2
//
//  Created by jjs on 2020/3/25.
//  Copyright © 2020 jjs.cn. All rights reserved.
//

#include "EventHandler.hpp"


void EventHandler::Initiliaze_Event_Queue(deque<Process*> ProcessList)
{
    for (int i = 0; i < ProcessList.size(); i++)
    {
        Event* e = new Event(ProcessList[i],ProcessList[i]->AT,TRANS_TO_READY);
        Eventqueue.push_back(e);
    }
}


Event* EventHandler::get_event()
{
    if (Eventqueue.size() == 0)
        return nullptr;
    Event* event = Eventqueue.front();
    Eventqueue.pop_front();
    return event;

}
void EventHandler::remove_event(Process* pro)
{
    int i = 0;
    for (i; i < Eventqueue.size(); i++)
    {
        if (Eventqueue.at(i)->p->pid == pro->pid)
            break;
    }
    Eventqueue.erase(Eventqueue.begin() + i);
}

int EventHandler::get_next_event_time()
{
    if (Eventqueue.size() == 0)
        return 0;
    else
    {
        Event* event = Eventqueue.front();
        return event->timestamp;
    }
}

void EventHandler::put_event(Event* e)
{
    int i = 0;
    for (i; i < Eventqueue.size(); i++)
    {
        if (Eventqueue.at(i)->timestamp > e->timestamp)
            break;
    }
    std::deque<Event*>::iterator it = Eventqueue.begin() + i;
    Eventqueue.insert(it, e);
}
