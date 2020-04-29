#ifndef Varib_hpp
#define Varib_hpp
#include "Process.hpp"
#include <deque>

using namespace std;

extern frame_t** frametable;
extern deque<Process*> processQueue;

extern unsigned long long cycles;
extern unsigned long long inst_count;
extern unsigned long long contextswitches;
extern unsigned long long processexits;
extern unsigned long long cost;

extern int ProcessNum;
extern int FrameNum ;
extern int ProcessCount;
extern const int PageTable_Size;
extern bool O;
extern bool P;
extern bool F;
extern bool S;
extern bool x;
extern bool y;
extern bool a;
extern bool f;

class Varib
{
};

#endif 