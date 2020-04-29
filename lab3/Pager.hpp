#ifndef Pager_hpp
#define Pager_hpp
#include "Varib.hpp"
#include "Process.hpp"
#include "Random.hpp"


using namespace std;

class Pager
{
public:
	int Framenum;
	virtual frame_t* select_victim_frame() { return nullptr;};
};

class FIFO_Pager : public Pager
{
public:
	int victimindex=-1;
	frame_t* select_victim_frame();
};

class Random_Pager : public Pager
{
public:
	int rof = -1;
	frame_t* select_victim_frame();
};

class Clock_Pager : public Pager
{
public:
	int victimindex=-1;
	frame_t* select_victim_frame();
};

class NRU_Pager : public Pager
{
public:
	int currenttime = 0;
	int tau = 49;
	int victimindex=-1;
	frame_t* select_victim_frame();
};

class Aging_Pager : public Pager
{
public:
	int victimindex=-1;
	frame_t* select_victim_frame();
};

class WorkingSet_Pager : public Pager
{
public:
	int tau = 49;
	int victimindex=-1;
	frame_t* select_victim_frame();
};

#endif 
