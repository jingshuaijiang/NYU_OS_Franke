#ifndef InputHandler_hpp
#define InputHandler_hpp

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <deque>
#include <vector>
#include "Varib.hpp"
#include "Process.hpp"
#include "Pager.hpp"
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
using namespace std;

class InputHandler
{
public:

	bool get_next_instruction(ifstream & input,char &operation, int &vpage);
	void Initialize_ProcessList(ifstream& in, deque<Process*>* ProcessList);
	void Initialize_ProcessPstats(stats*);
	void Initialize_ProcessPageTable(pte_t& page);
	void Initialize_FrameTable( deque<frame_t*>* freepool);
	Pager* argmentParse(int argc, char** argv);
};

#endif 