#include "Pager.hpp"

frame_t* FIFO_Pager::select_victim_frame()
{
	victimindex = (victimindex == (Framenum-1)) ? 0 : victimindex + 1;
	return frametable[victimindex];
}

frame_t* Random_Pager::select_victim_frame()
{
	rof++;
	int index = myrandom(rof, Framenum);
	frame_t* rframe = frametable[index];
	return rframe;
}

frame_t* Clock_Pager::select_victim_frame()
{
	victimindex = (victimindex == (Framenum - 1)) ? 0 : victimindex + 1;
	while (processQueue[frametable[victimindex]->process]->pageTable[frametable[victimindex]->vmp].REFERENCED == 1)
	{
		processQueue[frametable[victimindex]->process]->pageTable[frametable[victimindex]->vmp].REFERENCED = 0;
		victimindex = (victimindex == (Framenum - 1)) ? 0 : victimindex + 1;
	}
	return frametable[victimindex];
}

frame_t* NRU_Pager::select_victim_frame()
{
	int class1 = -1;
	int class2 = -1;
	int class3 = -1;
	int class4 = -1;
	victimindex = (victimindex == (Framenum - 1)) ? 0 : victimindex + 1;
	//if time is passed then reset the r bit.
	if (inst_count - currenttime +1> tau)
	{
		currenttime = inst_count+1;
		for (int i = 0; i < Framenum; i++)
		{
			if (processQueue[frametable[victimindex]->process]->pageTable[frametable[victimindex]->vmp].REFERENCED == 0)
			{
				if (processQueue[frametable[victimindex]->process]->pageTable[frametable[victimindex]->vmp].MODIFIED == 0)
				{
					class1 = (class1 == -1) ? victimindex : class1;
				}
				else
				{
					class2 = (class2 == -1) ? victimindex : class2;
				}
			}
			else
			{
				processQueue[frametable[victimindex]->process]->pageTable[frametable[victimindex]->vmp].REFERENCED = 0;
				if (processQueue[frametable[victimindex]->process]->pageTable[frametable[victimindex]->vmp].MODIFIED == 0)
				{
					class3 = (class3 == -1) ? victimindex : class3;
				}
				else
				{
					class4 = (class4 == -1) ? victimindex : class4;
				}
			}
			victimindex = (victimindex == (Framenum - 1)) ? 0 : victimindex + 1;
		}
	}
	else // traverse and return class1 or record the lowest class
	{
		for (int i = 0; i < Framenum; i++)
		{
			if (processQueue[frametable[victimindex]->process]->pageTable[frametable[victimindex]->vmp].REFERENCED == 0)
			{
				if (processQueue[frametable[victimindex]->process]->pageTable[frametable[victimindex]->vmp].MODIFIED == 0)
				{
					return frametable[victimindex];
				}
				else
				{
					class2 = (class2 == -1) ? victimindex : class2;
				}
			}
			else
			{
				if (processQueue[frametable[victimindex]->process]->pageTable[frametable[victimindex]->vmp].MODIFIED == 0)
				{
					class3 = (class3 == -1) ? victimindex : class3;
				}
				else
				{
					class4 = (class4 == -1) ? victimindex : class4;
				}
			}
			victimindex = (victimindex == (Framenum - 1)) ? 0 : victimindex + 1;
		}
	}
	if (class1 != -1)
	{
		victimindex = class1;
	}
	else if (class2 != -1)
	{
		victimindex = class2;
	}
	else if (class3 != -1)
	{
		victimindex = class3;
	}
	else if (class4 != -1)
	{
		victimindex = class4;
	}
	return frametable[victimindex];
}

frame_t* Aging_Pager::select_victim_frame()
{
	victimindex = (victimindex == (Framenum - 1)) ? 0 : victimindex + 1;
	for (int i = 0; i < Framenum; i++)
	{
		frametable[i]->age = frametable[i]->age >> 1;
		if (processQueue[frametable[i]->process]->pageTable[frametable[i]->vmp].REFERENCED == 1)
		{
			frametable[i]->age = (frametable[i]->age | 0x80000000);
			processQueue[frametable[i]->process]->pageTable[frametable[i]->vmp].REFERENCED = 0;
		}
	}
	int min = victimindex;
	for (int i = 0; i < Framenum; i++)
	{
		if (frametable[min]->age == 0)
		{
			victimindex = min;
			return frametable[min];
		}
		if (frametable[min]->age < frametable[victimindex]->age)
		{
			victimindex = min;
		}
		min  = (min == (Framenum - 1)) ? 0 : min + 1;
	}
	frametable[victimindex]->age = 0x00000000;
	return frametable[victimindex];
}

frame_t* WorkingSet_Pager::select_victim_frame()
{
	if (inst_count == 20)
	{
		printf("");
	}
	victimindex = (victimindex == (Framenum - 1)) ? 0 : victimindex + 1;
	int min = victimindex;
	for (int i = 0; i < Framenum; i++)
	{
		if (processQueue[frametable[min]->process]->pageTable[frametable[min]->vmp].REFERENCED ==0)
		{
			if (inst_count - frametable[min]->currenttime > tau)
			{
				victimindex = min;
				return frametable[victimindex];
			}
		}
		if (processQueue[frametable[min]->process]->pageTable[frametable[min]->vmp].REFERENCED == 1)
		{
			processQueue[frametable[min]->process]->pageTable[frametable[min]->vmp].REFERENCED = 0;
			frametable[min]->currenttime = inst_count;
		}
		min = (min == (Framenum - 1)) ? 0 : min + 1;
	}
	int mint = inst_count - frametable[victimindex]->currenttime;
	for (int i = 0; i < Framenum; i++)
	{
		if ((inst_count - frametable[min]->currenttime) > mint)
		{
			mint = inst_count - frametable[min]->currenttime;
			victimindex = min;
		}
		min = (min == (Framenum - 1)) ? 0 : min + 1;
	}
	frametable[victimindex]->currenttime = inst_count;
	return frametable[victimindex];
}
