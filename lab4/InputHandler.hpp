#ifndef InputHandler_hpp
#define InputHandler_hpp
#include "Varib.hpp"
#include "Scheduler.hpp"
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>




class InputHandler
{
public:
	Scheduler* argmentParse(int argc, char** argv);
	bool get_next_instruction(ifstream& in, int& time, int& track);
	void Construct_Input_IO_request(ifstream& in);
};

#endif 