#include "InputHandler.hpp"


Pager* InputHandler::argmentParse(int argc, char** argv)
{
    int c;
    char* content;
    Pager* pager = new Pager();
    while ((c = getopt(argc, argv, "f:a:o:")) != -1)
    {
        switch (c)
        {
        case 'f': {
            FrameNum = atoi(optarg);
            break;
        }
        case 'a': {
            content = optarg;
            switch (*content)
            {
            case 'f': {
                pager = new FIFO_Pager();
                pager->Framenum = FrameNum;
                break;
            }
            case 'r': {
                pager = new Random_Pager();
                pager->Framenum = FrameNum;
                break;
            }
            case 'c': {
                pager = new Clock_Pager();
                pager->Framenum = FrameNum;
                break;
            }
            case 'e': {
                pager = new NRU_Pager();
                pager->Framenum = FrameNum;
                break;
            }
            case 'a': {
                pager = new Aging_Pager();
                pager->Framenum = FrameNum;
                break;
            }
            case 'w': {
                pager = new WorkingSet_Pager();
                pager->Framenum = FrameNum;
                break;
            }
            }                  
            break;
        }
        case 'o': {
            content = optarg;
            while (*content)
            {
                switch (*content)
                {
                case 'O':
                    O = true;
                    break;
                case 'S':
                    S = true;
                    break;
                case 'F':
                    F = true;
                    break;
                case 'P':
                    P = true;
                    break;
                case 'x':
                    x = true;
                    break;
                case 'y':
                    y = true;
                    break;
                case 'f':
                    f = true;
                    break;
                case 'a':
                    a = true;
                    break;
                }
                content++;
            }
            break;
        }
        }
    }
    return pager;
}



bool InputHandler::get_next_instruction(ifstream& in, char& operation, int& vpage)
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
        sscanf(c, "%c %d", &operation, &vpage);
        return true;

    }
    return false;
}


void InputHandler::Initialize_ProcessList(ifstream& in, deque<Process*>* ProcessList)
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
            return;
        sscanf(c, "%d", &ProcessNum);
        for (int i = 0; i < ProcessNum; i++)
        {
            Process* process = new Process(i);
            process->pstats = new stats;
            Initialize_ProcessPstats(process->pstats);
            process->pageTable = new pte_t[PageTable_Size];
            for (int j = 0; j < PageTable_Size; j++)
            {
                Initialize_ProcessPageTable(process->pageTable[j]);
            }
            in.getline(c, 1000);
            while (c[0] == '#' && !in.eof())
            {
                in.getline(c, 1000);
            }
            int vma_num;
            sscanf(c, "%d", &vma_num);
            process->VMA = new vma[vma_num];
            process->VMA_NUM= vma_num;
            for (int j = 0; j < vma_num; j++) {
                in.getline(c, 1000);
                sscanf(c, "%d %d %d %d", &process->VMA[j].starting_virtual_page, 
                    &process->VMA[j].ending_virtual_page,
                    &process->VMA[j].write_protected,
                    &process->VMA[j].filemapped);
            }
            ProcessList->push_back(process);
        }        
    }
    return;
}

void InputHandler::Initialize_ProcessPageTable(pte_t& page)
{
    page.MODIFIED = 0;
    page.PAGEDOUT = 0;
    page.PRESENT = 0;
    page.REFERENCED = 0;
    page.FILEMAPPED = 0;
    page.WRITE_PROTECT = 0;
    page.PHYSICAL_FRAME = 0;
}

void InputHandler::Initialize_FrameTable(deque<frame_t*>* freepool)
{
    frametable = new frame_t * [FrameNum];
    for (int i = 0; i < FrameNum; i++)
    {
        frame_t* fff = new frame_t;
        frametable[i] = fff;
        frametable[i]->frameindex = i;
        frametable[i]->process = 0;
        frametable[i]->Mapped = 0;
        freepool->push_back(fff);
    }
}

void InputHandler::Initialize_ProcessPstats(stats* pstats)
{
    pstats->fins = 0;
    pstats->fouts = 0;
    pstats->ins = 0;
    pstats->maps = 0;
    pstats->unmaps = 0;
    pstats->zeros = 0;
    pstats->segprot = 0;
    pstats->segv = 0;
    pstats->outs = 0;
}