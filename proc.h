//
// Created by jj on 2/6/19.
//

#ifndef SCHED_PROC_H
#define SCHED_PROC_H

#include <stdio.h>

typedef struct proc {
    int num;
    int whereAt;
    int priority;
    int execTime;
    int memory;
    int openCount;
    FILE * fp;
}proc;

int openProc(int num);
int getNumber();
void closeProc();
int getPriority();
int getWhereAt();
int getTime();
void setTime(int time);
int getNext();
int getMemory();
#endif //SCHED_PROC_H
