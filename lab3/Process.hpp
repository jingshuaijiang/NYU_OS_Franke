#ifndef Process_hpp
#define Process_hpp

typedef struct {
	unsigned PRESENT : 1;
	unsigned WRITE_PROTECT : 1;
	unsigned MODIFIED : 1;
	unsigned REFERENCED : 1;
	unsigned PAGEDOUT : 1;
	unsigned FILEMAPPED : 1;
	unsigned PHYSICAL_FRAME : 7;
} pte_t;

typedef struct {
	int frameindex;
	int vmp;
	int process;
	unsigned Mapped : 1;
	unsigned long long currenttime;
	unsigned age : 32;
} frame_t;

typedef struct {
	unsigned long unmaps;
	unsigned long maps;
	unsigned long ins;
	unsigned long outs;
	unsigned long fins;
	unsigned long fouts;
	unsigned long zeros;
	unsigned long segv;
	unsigned long segprot;
} stats;

typedef struct {
	int starting_virtual_page;
	int	ending_virtual_page;
	int write_protected;
	int filemapped ;
} vma;

class Process
{
public:
	int pid;
	pte_t* pageTable;
	vma* VMA;
	stats* pstats;
	int VMA_NUM;
	Process(int id) { pid = id; }
	Process() {}
	bool inVMA(int vpage);
};


#endif 