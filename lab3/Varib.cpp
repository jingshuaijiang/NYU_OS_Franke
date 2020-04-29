#include "Varib.hpp"


const int PageTable_Size = 64;
int FrameNum = 16;
int ProcessNum = 1;
 bool O = false;
 bool P = false;
 bool F = false;
 bool S = false;
 bool x = false;
 bool y = false;
 bool a = false;
 bool f = false;
int ProcessCount = 1;
unsigned long long cycles=0;
unsigned long long inst_count=0;
unsigned long long contextswitches=0;
unsigned long long processexits=0;
unsigned long long cost=0;
frame_t** frametable;
deque<Process*> processQueue;