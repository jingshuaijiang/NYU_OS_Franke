#include "Process.hpp"
bool Process::inVMA(int vpage)
{
	for (int i = 0; i < this->VMA_NUM; i++)
	{
		if (this->VMA[i].starting_virtual_page <= vpage && vpage <= this->VMA[i].ending_virtual_page)
		{
			this->pageTable[vpage].FILEMAPPED = this->VMA[i].filemapped;
			this->pageTable[vpage].WRITE_PROTECT = this->VMA[i].write_protected;
			return true;
		}
	}
	return false;
}