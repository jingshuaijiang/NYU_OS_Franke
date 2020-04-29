// lab3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <deque>
#include "Varib.hpp"
#include "Process.hpp"
#include "Pager.hpp"
#include "InputHandler.hpp"
#include "Random.hpp"
#include "OutputHandler.hpp"





deque<frame_t*> freepool;
InputHandler ih;
Random rom;
OutputHandler oh;


void NOTinVMA(Process* process)
{
    if (O)
    {
        printf(" SEGV\n");
    }
    process->pstats->segv++;
    cycles += 240;
}

frame_t* allocate_frame_from_free_list()
{
    if (!freepool.empty())
    {
        frame_t* f = freepool.front();
        freepool.pop_front();
        return f;
    }
    return NULL;
}

frame_t* get_frame(Pager* pager)
{
    frame_t* frame = allocate_frame_from_free_list();
    if (frame == NULL) frame = pager->select_victim_frame();
    return frame;
}

void PagefaultHandler(Process* current_process,Pager* pager,int vpage, char operation)
{
    frame_t* newframe = get_frame(pager);
    //do something to deal with the victim page
    if (newframe->Mapped == 1)
    {
        if (O)
        {
            printf(" UNMAP %d:%d\n", newframe->process, newframe->vmp);
        }
        processQueue[newframe->process]->pstats->unmaps++;
        cycles += 400;
        if (processQueue[newframe->process]->pageTable[newframe->vmp].MODIFIED == 1)
        {
            if (processQueue[newframe->process]->pageTable[newframe->vmp].FILEMAPPED == 1)
            {
                if (O)
                {
                    printf(" FOUT\n");
                }
                cycles += 2500;
                processQueue[newframe->process]->pstats->fouts++;
            }
            else
            {
                if (O)
                {
                    printf(" OUT\n");
                }
                cycles += 3000;
                processQueue[newframe->process]->pageTable[newframe->vmp].PAGEDOUT = 1;
                processQueue[newframe->process]->pstats->outs++;
            }
            processQueue[newframe->process]->pageTable[newframe->vmp].MODIFIED = 0;            
        }
        processQueue[newframe->process]->pageTable[newframe->vmp].PRESENT=0;
        
    }
    newframe->Mapped = 1;
    newframe->process = current_process->pid;
    newframe->vmp = vpage;
    current_process->pageTable[vpage].PRESENT = 1;
    current_process->pageTable[vpage].PHYSICAL_FRAME = newframe->frameindex;
    if (current_process->pageTable[vpage].FILEMAPPED == 1)
    {
        if (O)
        {
            printf(" FIN\n");
        }
        //if (current_process->pid == 0 && vpage==33)
        //{
        //    printf("");
        //}
        current_process->pstats->fins++;
        cycles += 2500;
    }
    else if (current_process->pageTable[vpage].PAGEDOUT == 1)
    {
        if (O)
        {
            printf(" IN\n");
        }
        current_process->pstats->ins++;
        cycles += 3000;
    }
    else
    {
        if (O)
        {
            printf(" ZERO\n");
        }
        current_process->pstats->zeros++;
        cycles += 150;
    }
    if (O)
    {
        printf(" MAP %d\n", newframe->frameindex);
    }
    current_process->pstats->maps++;
    cycles += 400;
    
}

void simulation(ifstream &input, Pager* pager)
{
    char operation;
    int vpage;
    ih.Initialize_ProcessList(input, &processQueue);
    ih.Initialize_FrameTable(&freepool);
    Process* current_process = new Process;
    while (ih.get_next_instruction(input,operation, vpage)) {
    
        switch (operation)
        {
        case 'c':
        {
            oh.Output_Instruction(operation, vpage);
            current_process = processQueue[vpage];
            contextswitches += 1;
            cycles += 121;
            break;
        }
        case 'r':
        {
            //if (current_process->pid == 0 && vpage == 33)
            //{
            //    printf("");
            //}
            oh.Output_Instruction(operation, vpage);
            cycles += 1;
            if (!current_process->inVMA(vpage))
            {
                NOTinVMA(current_process);
                break;
            }
            current_process->pageTable[vpage].REFERENCED = 1;
            if (current_process->pageTable[vpage].PRESENT == 0)
            {
                PagefaultHandler(current_process,pager,vpage,operation);
            }
            break;
            
        }
        case 'w':
        {
            //if (current_process->pid == 0 && vpage == 33)
            //{
            //    printf("");
            //}
            oh.Output_Instruction(operation, vpage);
            cycles += 1;
            if (!current_process->inVMA(vpage))
            {
                NOTinVMA(current_process);
                break;
            }
            current_process->pageTable[vpage].REFERENCED = 1;
            current_process->pageTable[vpage].MODIFIED = 1;
            if (current_process->pageTable[vpage].PRESENT == 0)
            {
                PagefaultHandler(current_process, pager, vpage, operation);
            }
            break;
        }
        case 'e':
        {
            if (O) {
                printf("%llu: ==> %c %d\n", inst_count, operation, vpage);
                printf("EXIT current process %d\n", current_process->pid);
            }
            processexits += 1;
            cycles += 175;
            for (int i = 0; i < PageTable_Size; i++)
            {
                if (current_process->pageTable[i].PRESENT == 1)
                {
                    frame_t* mappedframe = frametable[current_process->pageTable[i].PHYSICAL_FRAME];
                    if (O)
                    {
                        printf(" UNMAP %d:%d\n", current_process->pid, mappedframe->vmp);
                    }
                    current_process->pstats->unmaps++;
                    cycles += 400;
                    if (current_process->pageTable[i].MODIFIED == 1 && current_process->pageTable[i].FILEMAPPED == 1)
                    {
                        if (O)
                        {
                            printf(" FOUT\n");
                        }
                        current_process->pstats->fouts++;
                        cycles += 2500;
                    }
                    mappedframe->Mapped = 0;
                    mappedframe->vmp = 0;
                    mappedframe->process = 0;
                    mappedframe->age = 0x00000000;
                    freepool.push_back(mappedframe);                    
                }
                current_process->pageTable[i].PRESENT = 0;
                current_process->pageTable[i].PAGEDOUT = 0;
            }
            break;
        }
           
        }
        if (operation == 'w' && current_process->pageTable[vpage].WRITE_PROTECT == 1)
        {
            current_process->pageTable[vpage].MODIFIED = 0;
            current_process->pstats->segprot++;
            oh.Output_Segprot();
            cycles += 300;
        }
        inst_count += 1;

    }
}
int main(int argc, char** argv)
{
    ifstream input(argv[argc-2]);
    ifstream random(argv[argc-1]);
    rom.Read_Random_File(random);
    Pager* pager = ih.argmentParse(argc, argv);
    simulation(input, pager);
    oh.Output();
    return 0;
}
