#pragma once
#include <stdio.h>
#include <queue>
#include "Event.h"


class Scheduler
{
public:
	queue<Process*> runqueue;
	virtual void add_process(Process* pro) { return; };
	virtual Process* get_next_process() { Process* temp = new Process; return temp; };
};
class FIFS_Scheduler :public Scheduler {
public:
    void add_process(process* pro);
    process* get_next_process();
};

class LCFS_Scheduler :public Scheduler {
public:
    runQueue runqueue;
    void add_process(process* pro);
    process* get_next_process();
};

class SRTF_Scheduler :public Scheduler {
public:
    runQueue runqueue;
    void add_process(process* pro);
    process* get_next_process();
};

class RR_Scheduler :public Scheduler {
    void add_process(process* pro);
    process* get_next_process();
};

class PRIO_Scheduler :public Scheduler {
public:
    queue<process*> runqueue[2][4];

    void add_process(process* pro);
    void swap_queue();
    process* get_next_process();
    bool is_queue_empty(queue<process*>* rq);
};

