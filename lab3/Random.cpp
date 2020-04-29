#include "Random.hpp"
int ofs = 0;
int LINE_LENGTH = 1000;
int* randvals;
char* linearray;
int filelength;

int myrandom(int rof,int size) {
    int result = randvals[rof % filelength] % size;
    return result;
}


void Random::Read_Random_File(ifstream& randomfile)
{
    int index = 0;
    linearray = new char[LINE_LENGTH];
    randomfile.getline(linearray, LINE_LENGTH);
    filelength = stoi(string(linearray));
    randvals = new int[filelength];
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