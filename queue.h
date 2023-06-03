#ifndef __queue__
#define __queue__ 1

#include <stdio.h>
#include <stdlib.h>

/*queue stucture*/
struct queue {
    char key;
    int arrivalTime;
    struct queue *next;
};
typedef struct queue QUEUE;

/*queue function prototypes*/
extern void enqueue (QUEUE **, char, int);
extern int dequeue (QUEUE **);
extern int getSize (QUEUE *);
#endif


