// lab4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "InputHandler.hpp"
#include "OutputHandler.hpp"
#include "IORequest.hpp"
#include "Varib.hpp"

using namespace std;

InputHandler ih;
OutputHandler oh;

void simulation(Scheduler* scheduler)
{
    IORequest* CurrentIORequest = nullptr;
    bool complete = false;
    IORequest* frontrequest = nullptr;
    while (true)
    {
        frontrequest = NULL;
        if (!InputIOQueue.empty())
        {
            frontrequest = InputIOQueue.front();
            if (frontrequest->arrive_time == total_time)
            {
                scheduler->add_request(frontrequest);
                InputIOQueue.pop_front();
            }
        }
        if (CurrentIORequest != NULL)
        {
            if (current_track == CurrentIORequest->track)
            {
                CurrentIORequest->end_time = total_time;
                if (total_time == 88)
                {
                    printf("");
                }
                CurrentIORequest = NULL;
                complete = true;
            }
            else
            {
                direction = (CurrentIORequest->track > current_track) ? 1 : -1;
                current_track += direction;
                tot_movement += 1;
            }
        }
        if (CurrentIORequest == NULL && !scheduler->NOpending())
        {
            CurrentIORequest = scheduler->get_next_request();
            if (CurrentIORequest->start_time == -1)
            {
                CurrentIORequest->start_time = total_time;
                continue;
            }
            if (complete)
            {
                complete = false;
                continue;
            }
        }

        if (CurrentIORequest == NULL && frontrequest == NULL && scheduler->NOpending() && InputIOQueue.empty())
        {
            break;
        }
        total_time += 1;
    }
}

int main(int argc, char** argv)
{
    ifstream input(argv[argc-1]);
    Scheduler* scheduler = ih.argmentParse(argc,argv);
    ih.Construct_Input_IO_request(input);
    simulation(scheduler);
    oh.PrintIORequest();
}
