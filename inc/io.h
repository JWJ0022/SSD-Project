#ifndef IO_H
#define IO_H

#include <string>
using namespace std;

#define NAND_FILE "../data/nand.txt"
#define RESULT_FILE "../data/result.txt"
#define TEMP_FILE "../data/temp.txt"
#define MAX_LINES 100  

void io_read(int idx);
void io_write(int index, string data);
void fullwrite(string data);  
void fullread();              

#endif
