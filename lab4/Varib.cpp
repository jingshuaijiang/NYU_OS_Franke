#include "Varib.hpp"

int total_tim = 0 ;
int total_time = 0;
int tot_movement = 0;
int max_waittime = 0;
int total_waittime = 0;
int total_turnaround_time = 0;
int requestnum = 0;
double avg_turnaround = 0;
double avg_waittime = 0;
int current_track = 0;
int direction = 1;
deque<IORequest*> InputIOQueue;
deque<IORequest*> InputIOqueue;