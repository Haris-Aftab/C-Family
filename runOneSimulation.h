#ifndef __RUNONESIMULATION__
#define __RUNONESIMULATION__1

/*boolean datatype*/
#define TRUE 1
#define FALSE 0
typedef char BOOLEAN;

#include "queue.h"
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <sys/time.h>
#include <gsl/gsl_randist.h>

/*stores runOneSimulation's results*/
struct results {
   int lTotalVehiclesPassed, rTotalVehiclesPassed;
   float lAvgWaitTime, rAvgWaitTime;
   int lMaxWaitTime, rMaxWaitTime;
   int lClearQueueTime, rClearQueueTime;
};
typedef struct results RESULTS;

/*runOneSimulation's function prototypes*/
extern RESULTS runOneSimulation(int, int, int, int);
extern float getRandomChoice();
extern int roundNo(float);
extern void leftLightGreen(BOOLEAN *, BOOLEAN *);
extern void rightLightGreen(BOOLEAN *, BOOLEAN *);
extern void lightSwitch(BOOLEAN *, BOOLEAN *);

#endif

