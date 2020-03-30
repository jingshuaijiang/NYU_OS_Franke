//
//  InputHandler.cpp
//  Lab2
//
//  Created by jjs on 2020/3/25.
//  Copyright © 2020 jjs.cn. All rights reserved.
//

#include "InputHandler.hpp"

void InputHandler::Read_Random_File(ifstream& randomfile)
{
    int index = 0;
    linearray = new char[LINE_LENGTH];
    randomfile.getline(linearray, LINE_LENGTH);
    int filelength = stoi(string(linearray));
    randvals = new int[filelength + 1];
    while (!randomfile.eof())
    {
        delete[] linearray;
        linearray = new char[LINE_LENGTH];
        randomfile.getline(linearray, LINE_LENGTH);
        if (randomfile.eof())
            break;
        randvals[index] = stoi(string(linearray));
        index += 1;
    }
}

int InputHandler::myrandom(int burst) {
    ofs = ofs %40000 ;
    return 1 + (randvals[ofs] % burst);
}

void InputHandler::Read_Input_File(ifstream& inputfile, deque<Process*>* ProcessList)
{
    string line;
    const char* delim = " '\t''\n'";
    int pid = 0;
    int processInfo[4];
    while (getline(inputfile, line))
    {
        int i = 0;
        char* dup;
        char* token;
        dup = strdup(line.c_str());
        token = strtok(dup, delim);
        while (token != NULL) {
            processInfo[i] = atoi(token);
            i++;
            token = strtok(NULL, delim);
        }
        Process* p = new Process();
        p->pid = pid;
        p->AT = processInfo[0];
        p->TC = processInfo[1];
        p->CB = processInfo[2];
        p->IO = processInfo[3];
        p->RC = p->TC;
        p->static_Prio = myrandom(maxprio);
        p->dynamic_Prio = p->static_Prio - 1;
        p->state_ts = p->AT;
        ProcessList->push_back(p);
        free(dup);
        pid++;
        ofs++;
    }
}
Scheduler* InputHandler::argmentParse(int argc, char** argv)
{
    int c;
    Scheduler* s = new Scheduler();
    while ((c = getopt(argc, argv, "vs:")) != -1)
    {
        switch (c)
        {
        case 'v': {
            verbose = 1;
            break;
        }

        case 's': {
            switch (optarg[0])
            {
            case 'F': {
                s = new FCFS_Scheduler();
                type = "FCFS";

                break;
            }

            case 'L': {
                s = new LCFS_Scheduler();
                type = "LCFS";

                break;
            }

            case 'S': {
                s = new SRTF_Scheduler();
                type = "SRTF";

                break;
            }
            case 'R': {
                quantum = atoi(&optarg[1]);
                type = "RR";
                if (quantum != 10000)
                {
                    type = type + " "+to_string(quantum);
                }
                preprio = 2;
                s = new RR_Scheduler();
                break;
            }
            case 'P': {
                sscanf(optarg, "%*c%d:%d", &quantum, &maxprio);
                s = new PRIO_Scheduler(maxprio);
                type = "PRIO";
                if (quantum != 10000)
                {
                    type = type + " "+to_string(quantum);
                }

                break;
            }
            case 'E': {
                sscanf(optarg, "%*c%d:%d", &quantum, &maxprio);
                s = new PRIO_Scheduler(maxprio);
                preprio = 1;
                type = "PREPRIO";
                if (quantum != 10000)
                {
                    type = type + " "+to_string(quantum);
                }
                break;
            }
                    break;
            }
        


        }
        }
    }
    return s;
}
