#include <stdio.h>
#include <stdlib.h>
//Generator for disk requests
//Put out time, block number, and process id

int time = 0;

int main (void) {
    for(int i = 0; i < 10000; i++ ){
        time += rand() % 11; //Good enough 
        int block = rand() % (1 << 20);
        int proc = rand() % 100;
        printf("%d %d %d\n",time, block, proc); //Prints out time, block number, and proc id
    }
}
