#ifndef Scheduler_hpp
#define Scheduler_hpp
#include <deque>
#include <stdio.h>
#include <stdlib.h>
#include "Varib.hpp"
#include "IORequest.hpp"

using namespace std;

class Scheduler
{
public:
	deque<IORequest*> IOQueue;
	virtual bool NOpending() { return false; };
	virtual void add_request(IORequest* request) { return; };
	virtual IORequest* get_next_request() { return nullptr; };
};

class FIFO_Scheduler : public Scheduler
{
public:
	void add_request(IORequest* request);
	IORequest* get_next_request();
	bool NOpending();
};

class SSTF_Scheduler : public Scheduler
{
public:
	void add_request(IORequest* request);
	IORequest* get_next_request();
	bool NOpending();
};

class LOOK_Scheduler : public Scheduler
{
public:
	void add_request(IORequest* request);
	IORequest* get_next_request();
	bool NOpending();
};

class CLOOK_Scheduler : public Scheduler
{
public:
	void add_request(IORequest* request);
	IORequest* get_next_request();
	bool NOpending();
};

class FLOOK_Scheduler : public Scheduler
{
public:
	deque<IORequest*>* addqueue = new deque<IORequest*>;
	deque<IORequest*>* activequeue = new deque<IORequest*>;
	void add_request(IORequest* request);
	IORequest* get_next_request();
	bool NOpending();
};


#endif 