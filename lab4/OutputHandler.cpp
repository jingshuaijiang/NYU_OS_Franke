#include "OutputHandler.hpp"


void OutputHandler::PrintIORequest()
{
	int waittime = 0;
	int turnaroundtime = 0;
	while (!InputIOqueue.empty())
	{
		IORequest* iorequest = InputIOqueue.front();
		InputIOqueue.pop_front();
		printf("%5d: %5d %5d %5d\n", iorequest->rid, iorequest->arrive_time, iorequest->start_time, iorequest->end_time);
		waittime = iorequest->start_time - iorequest->arrive_time;
		turnaroundtime = iorequest->end_time - iorequest->arrive_time;
		if (waittime > max_waittime)
		{
			max_waittime = waittime;
		}
		total_waittime += waittime;
		total_turnaround_time += turnaroundtime;
	}
	avg_turnaround = (double)total_turnaround_time / requestnum;
	avg_waittime = (double)total_waittime / requestnum;
	printf("SUM: %d %d %.2lf %.2lf %d\n", total_time, tot_movement, avg_turnaround, avg_waittime,  max_waittime);
	
}
