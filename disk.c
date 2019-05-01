#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "disk.h"
//Disk program to handle disk requests
//Loads the queue then process the queue over and over again
//Keep doing until the file empties

request * q[10000];
int qi = 0;
int time = 10;
int t = 0;
int inOrOut = 1;
int filein, fileout;

void enqueue(request * in) {
    q[qi++] = in;
}
request * dequeue(int pos) {
    request * r = q[pos];
    q[pos] = q[--qi];
    return r;
}

int load_q(int time) {//time tells us what time it is in disk time
        //Disk uses time to enqueue everything smaller than or equal to 
        //what time it is
    int loc;
    int proc;
    while(t <= time && !feof(file)) {
        request * x = malloc(sizeof(request));
        fscanf(file, "%d%d%d\n", &t, &loc, &proc);
        x->loc = loc;
        x->proc = proc;
        enqueue(x);

    }
    return 0;
}
int getSmallestInd() {
    int tmp = q[0]->loc;
    int ind = 0;
    for(int i = 1; i < qi; i++) {
        if(q[i]->loc < tmp){
            tmp = q[i]->loc;
            ind = i;
        }
    }
    return ind;
}
int getLargestInd() {
    int tmp = q[0]->loc;
    int ind = 0;
    for(int i = 1; i < qi; i++) {
        if(q[i]->loc > tmp){
            tmp = q[i]->loc;
            ind = i;
        }
    }
    return ind;
}

int process() {
    while(qi > 0) {
        request * r;
        if(inOrOut) {
            r = dequeue(getSmallestInd());
            inOrOut = 1;
        }
        else {
            r = dequeue(getLargestInd());
            inOrOut = 0;
        }
        time+=5;
        printf("%d %d\n",r->proc, r->loc);
    }
    return 1;
}


int main (int argc, char** argv) {
    char * fifoin = "./diskin";
    char * fifoout = "./diskout";
    mkfifo(fifoin, 0666);
    filein = open(fifoin, O_WRONLY);
    fileout = open(fifoout, O_RDONLY);

    while(!feof(filein)) {
        load_q(time);
        if(qi <= 0)//If q not getting filled, increment some
            time+=5;
        process();
    }
    return 0;
}

