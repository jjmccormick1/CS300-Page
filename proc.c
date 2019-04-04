// proc.c
// Created by Jeremy McCormick on 2/6/19.
// CS300 Operating Systems Dr. Mayhew
// Scheduler Program
// This module is responsible for opening and closing process files. 
// Uses proc structure to hold all information.

#include <stdlib.h>
#include "proc.h"

FILE * fp;
int openCount = 0;
int number;
int openProc(int num) {
    char buf[100];
    openCount = 0;
    //Open with counter filename
    snprintf(buf, sizeof(buf), "%i.proc", num);
    fp = fopen(buf, "r+");
    if(fp == NULL){
        printf("File not found");
        return 1;
    }
    number = num;
    return 0;
}

void closeProc() {
    rewind(fp);
    fprintf(fp, "%09i", (getNumber() + openCount));
    fclose(fp);
}
int getNumber() {
    return number;
}
int getPriority() {
    fseek(fp, 10, SEEK_SET);
    int ret;
    fscanf(fp, "%d\n", &ret);
    return ret;
}
int getWhereAt() {
    rewind(fp);
    int ret;
    fscanf(fp, "%d\n", &ret);
    return ret;
}
int getTime() {
    fseek(fp, 10 * 2, SEEK_SET);
    int ret;
    fscanf(fp, "%d\n", &ret);
    return ret;
}
void setTime(int time) {
    fseek(fp, 10 * 2, SEEK_SET);
    fprintf(fp, "%9i", time);
}
int getMemory() {
    fseek(fp, 10 * 3, SEEK_SET);
    int ret;
    fscanf(fp, "%d\n", &ret);
    return ret;
}
int getNext() {
    if(fp == NULL)
        return -1;
    int pos = getWhereAt() + openCount;
    fseek(fp, (10 * 4) + pos * 3, SEEK_SET); //Goto end of proc info
    int next;
    int eof = fscanf(fp, "%d", &next);
    if(eof == EOF)
        return 0;
    openCount++;
    return next;
}

#ifdef TEST
/*int main(void) {
    openProc(0);
    printf("At Line: %i\n",getWhereAt());
    printf("Memory: %i\n",getMemory());
    printf("Exec Time: %i\n",getTime());
    printf("Priority: %i\n",getPriority());
    printf("next: %i\n",getNext());
    printf("next: %i\n",getNext());
    printf("next: %i\n",getNext());
    printf("next: %i\n",getNext());
    closeProc();
}*/
#endif
