#include "OutputHandler.hpp"


void OutputHandler::Output()
{
	if (P)
	{
		Output_ProcessList(processQueue);
	}
	if (F)
	{
		Output_FrameTable(frametable);
	}
	if (S)
	{
		Output_stats(processQueue);
		Output_Summary();
	}
}
void OutputHandler::Output_ProcessList(deque<Process*> ProcessList)
{
	for (int i = 0; i < ProcessList.size(); i++)
	{
		printf("PT[%d]: ", i);
		Process* process = ProcessList[i];
		Output_PageTable(process->pageTable);
		printf("\n");
	}
}

void OutputHandler::Output_PageTable(pte_t* page_table)
{
	for (int i = 0; i < PageTable_Size; i++)
	{
		if (page_table[i].PRESENT == 0 && page_table[i].PAGEDOUT == 1)
		{
			printf("# ");
		}
		else if (page_table[i].PRESENT == 0 && page_table[i].PAGEDOUT == 0)
		{
			printf("* ");
		}
		else
		{
			string content = to_string((long long int)(i)) + ':';
			content = (page_table[i].REFERENCED == 1) ? (content + 'R') : (content + '-');
			content = (page_table[i].MODIFIED == 1) ? (content + 'M') : (content + '-');
			content = (page_table[i].PAGEDOUT == 1) ? (content + 'S') : (content + '-');
			content = content + ' ';
			cout << content;
		}
	}
}

void OutputHandler::Output_FrameTable(frame_t** frametable)
{
	printf("FT: ");
	for (int i = 0; i < FrameNum; i++)
	{
		if(frametable[i]->Mapped ==1)
		{
			printf("%d:%d ", frametable[i]->process, frametable[i]->vmp);
		}
		else
		{
			printf("* ");
		}
	}
	cout << endl;

}

void OutputHandler::Output_stats(deque<Process*> ProcessList)
{
	for (int i = 0; i < ProcessNum; i++)
	{
		printf("PROC[%d]: U=%lu M=%lu I=%lu O=%lu FI=%lu FO=%lu Z=%lu SV=%lu SP=%lu\n",
			ProcessList[i]->pid,
			ProcessList[i]->pstats->unmaps, ProcessList[i]->pstats->maps, ProcessList[i]->pstats->ins, ProcessList[i]->pstats->outs,
			ProcessList[i]->pstats->fins, ProcessList[i]->pstats->fouts, ProcessList[i]->pstats->zeros,
			ProcessList[i]->pstats->segv, ProcessList[i]->pstats->segprot);
	}
}
void OutputHandler::Output_Summary()
{
	printf("TOTALCOST %lu %lu %lu %llu\n", inst_count, contextswitches, processexits, cycles);
}

void OutputHandler::Output_Instruction(char operation, int vpage)
{
	if (O)
	{
		printf("%llu: ==> %c %d\n", inst_count, operation, vpage);
	}
}
void OutputHandler::Output_Segprot()
{
	if (O)
	{
		printf(" SEGPROT\n");
	}
}
