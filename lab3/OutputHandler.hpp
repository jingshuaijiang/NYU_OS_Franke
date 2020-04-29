#ifndef OutputHandler_hpp
#define OutputHandler_hpp
#include <iostream>
#include "Varib.hpp"
#include <string>
#include "InputHandler.hpp"

using namespace std;

class OutputHandler
{
public:
	void Output();
	void Output_ProcessList(deque<Process*> ProcessList);
	void Output_PageTable(pte_t* page_table) ;
	void Output_FrameTable(frame_t** frametable);
	void Output_stats(deque<Process*> ProcessList) ;
	void Output_Summary() ;
	void Output_Instruction(char operation, int vpage);
	void Output_Segprot();
};

#endif 