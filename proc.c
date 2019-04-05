// proc.c
// Created by Jeremy McCormick on 2/6/19.
// CS300 Operating Systems Dr. Mayhew
// Scheduler Program
// This module is responsible for opening and closing process files. 
// Uses proc structure to hold all information.

#include <stdlib.h>
#include "proc.h"

proc * openProc(int num) {
    proc * proc1 = malloc(sizeof(proc));
    proc1->runStart = -1;
    proc1->openCount = 0;
    proc1->blockTime = -1;
    proc1->inMemory = 0;
    proc1->lastRunTime = -1;
    proc1->lastRunCount = 0;
    char buf[100];
    //Open with counter filename
    snprintf(buf, sizeof(buf), "%i.proc", num);
    proc1->fp = fopen(buf,"r");
    proc1->num = num;
    fscanf(proc1->fp,"%d\n%d\n%d\n%d\n",&proc1->whereAt, &proc1->priority, &proc1->execTime, &proc1->memory);
    if(proc1->whereAt > 0)
        fseek(proc1->fp, proc1->whereAt * 3, SEEK_CUR); // Goto where at, may be zero
    return proc1;
}

int closeProc(proc * proc1) {
    fclose(proc1->fp);
    char buf[100];
    //Open with counter filename
    snprintf(buf, sizeof(buf), "%i.proc", proc1->num);
    proc1->fp = fopen(buf,"r+");
    rewind(proc1->fp);
    fprintf(proc1->fp, "%i", proc1->whereAt);
    fclose(proc1->fp);
    free(proc1);
    return 1;
}
int getNumber(proc * proc1) {
    return proc1->num;
}
int getPriority(proc * proc1) {
    return proc1->priority;
}
int getWhereAt(proc * proc1) {
    return proc1->whereAt;
}
int getTime(proc * proc1) {
    return proc1->execTime;
}
void setTime(proc * proc1, int time) {
    proc1->execTime = time;
}
int getMemory(proc * proc1) {
    return proc1->memory;
}
int getNext(proc * proc1) {
    //Current at fp will be after info lines already after reading them
    int next;
    fscanf(proc1->fp, "%d\n", &next);
    if(next == EOF)
        return -1;
    proc1->whereAt++;
    return next;
}

#ifdef TEST
int main(void) {

    proc * proc1 = openProc(0);
    printf("At Line: %i\n",getWhereAt(proc1));
    printf("Memory: %i\n",getMemory(proc1));
    printf("Exec Time: %i\n",getTime(proc1));
    printf("Priority: %i\n",getPriority(proc1));
    printf("next: %i\n",getNext(proc1));
    printf("next: %i\n",getNext(proc1));
    printf("next: %i\n",getNext(proc1));
    printf("next: %i\n",getNext(proc1));
}
#endif
