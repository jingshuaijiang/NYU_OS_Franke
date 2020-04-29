#ifndef Random_hpp
#define Random_hpp
#include <fstream>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>

using namespace std;

extern int ofs;
extern int LINE_LENGTH;
extern int* randvals;
extern char* linearray;
extern int filelength;

extern int myrandom(int burst,int size);

class Random
{
public:
	int FrameNum;
	
	void Read_Random_File(ifstream& randomfile);
};


#endif 