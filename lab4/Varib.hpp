#ifndef Varib_hpp
#define Varib_hpp
#include <deque>
#include "IORequest.hpp"

using namespace std;
extern int total_waittime;
extern int total_turnaround_time;
extern int requestnum;
extern int total_time;
extern int tot_movement;
extern int max_waittime;
extern double avg_turnaround;
extern double avg_waittime;
extern int current_track;
extern int direction;
extern deque<IORequest*> InputIOQueue;
extern deque<IORequest*> InputIOqueue;

class Varib
{

};

#endif 