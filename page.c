//
// Created by jj on 4/11/19.
//

#include "page.h"

int memq[4096];
int memqTail = 0;
int diskq[4096];
int diskqTail = 0;


int getPageMem() {
    static int mem = 4095;
    if(mem)
        return mem--;
    else
        return memq[memqTail--];
}

void putPageMem(int page) {
    memq[memqTail++] = page;
}

int getDiskMem() {
    static int disk = 4095;
    if(disk)
        return diskqTail--;
    else
        return diskq[diskqTail--];
}

int putDiskMem(int page) {
    diskq[diskqTail++] = page;
}