#ifndef SSD_H
#define SSD_H

#include "../inc/io.h"

// 속성 정의
#define LBA_SIZE 4
#define MAX_LBA 100
#define INIT_DATA "0x00000000"

#define REGEX_PATTERN "^0x[0-9A-Fa-f]{8}$"

void ssd_read(int index);
void ssd_write(int index, string data);
void ssd_full_write(string data);
void ssd_full_read();

#endif
