#include "InputHandler.hpp"

Scheduler* InputHandler::argmentParse(int argc, char** argv)
{
    int c;
    char* content;
    Scheduler* scheduler = new Scheduler();
    while ((c = getopt(argc, argv, "s:")) != -1)
    {
        switch (c)
        {
        case 's': {
            content = optarg;
            switch (*content)
            {
            case 'i': {
                scheduler = new FIFO_Scheduler();
                break;
            }
            case 'j': {
                scheduler = new SSTF_Scheduler();
                break;
            }
            case 's': {
                scheduler = new LOOK_Scheduler();
                break;             
            }
            case 'c': {
                scheduler = new CLOOK_Scheduler();
                break;
            }
            case 'f': {
                scheduler = new FLOOK_Scheduler();
                break;
            }
            default:
                break;
            }
            
            break;
        }
        default:
            break;
        }
    }
    return scheduler;
}

bool InputHandler::get_next_instruction(ifstream& in, int& time, int& track)
{
    if (!in.eof())
    {
        char* c = new char[1000];
        in.getline(c, 1000);
        while (c[0] == '#' && !in.eof())
        {
            in.getline(c, 1000);
        }
        if (in.eof())
        {
            return false;
        }
        sscanf(c, "%d %d", &time, &track);
        return true;

    }
    return false;
}

void InputHandler::Construct_Input_IO_request(ifstream& in)
{
    int time = 0;
    int track = 0;
    int rid = 0;
    while (get_next_instruction(in, time, track))
    {
        IORequest* iorequest = new IORequest;
        iorequest->rid = rid;
        iorequest->arrive_time = time;
        iorequest->track = track;
        iorequest->start_time = -1;
        iorequest->end_time = -1;
        InputIOQueue.push_back(iorequest);
        InputIOqueue.push_back(iorequest);
        rid++;
    }
    requestnum = rid;
}

