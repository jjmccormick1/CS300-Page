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
    long runStart;
    long runEnd;
    int blockTime;
    long blockStart;
    int inMemory;
    long lastRunCount;
    long lastRunTime;
    FILE * fp;
}proc;


proc * openProc(int num);
int getNumber(proc * proc);
int closeProc(proc * proc1);
int getPriority(proc * proc1);
int getWhereAt(proc * proc1);
int getTime(proc * proc1);
void setTime(proc * proc1, int time);
int getNext(proc * proc1);
int getMemory(proc * proc1);
#endif //SCHED_PROC_H
