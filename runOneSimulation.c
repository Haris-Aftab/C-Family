#include "runOneSimulation.h"


/*calculates results based on parameters*/
extern RESULTS runOneSimulation(int lArriveRate, int rArriveRate, int lGreenTime, int rGreenTime) {
   /*initialisation*/
   RESULTS r;
   int i, j;
   int time = 0;
   int lightTime=0;
   r.lTotalVehiclesPassed = 0;
   r.rTotalVehiclesPassed = 0;
   r.lAvgWaitTime = 0.0;
   r.rAvgWaitTime = 0.0;
   r.lMaxWaitTime = 0;
   r.rMaxWaitTime = 0;
   r.lClearQueueTime = 0;
   r.rClearQueueTime = 0;
   int lArrivalTime = 0, rArrivalTime = 0;
   int waitTime = 0;
   BOOLEAN lGreen;
   BOOLEAN rGreen;
   /*
   QUEUE *qLeft;
   if (!(qLeft = (QUEUE *) malloc(sizeof(QUEUE)))) {
      fprintf(stderr, "Out of memory\n Left queue could not be made.\n");
      exit(1);
   }
   QUEUE *qRight;
      if (!(qRight = (QUEUE *) malloc(sizeof(QUEUE)))) {
         fprintf(stderr, "Out of memory\n Right queue could not be made.\n");
	 exit(1);
      }
    */
    /*create left and right queues*/
    QUEUE *qLeft = NULL;
    QUEUE *qRight = NULL;    
      
   /*initial light colour*/
    if (roundNo(getRandomChoice())){
        leftLightGreen(&lGreen, &rGreen);
    } else {
        rightLightGreen(&lGreen, &rGreen);
    }

    /*while the time < 500 or queues are not empty*/
    while (time < 500 || getSize(qLeft) != 0 || getSize(qRight) != 0) {
        /*set traffic light green period time*/
	if (lGreen == TRUE)
            lightTime = lGreenTime;
        else
            lightTime = rGreenTime;

        for (i=0; i < lightTime; i++) {
	    /*enqueue vehicles when time < 500*/
            if (time < 500) {
                time++;
                if (getRandomChoice()*100.0 <= lArriveRate)
                    enqueue(&qLeft,'L',time);

                if (getRandomChoice()*100.0 <= rArriveRate)
                    enqueue(&qRight,'R',time);
            } 
            /*dequeue left queue*/
            if (lGreen == TRUE) {
                if (getSize(qLeft) != 0) {
                    lArrivalTime = dequeue(&qLeft);
                    waitTime = time - lArrivalTime;
                    /*if time>=500, use clearQueueTime*/
                    if (time >= 500) {
                        r.lClearQueueTime++;
                        waitTime += r.lClearQueueTime;
                    }

                    r.lAvgWaitTime += waitTime;
                    if (waitTime > r.lMaxWaitTime)
                        r.lMaxWaitTime = waitTime;
                    r.lTotalVehiclesPassed++;  
                }
                if (time > 500 && getSize(qRight) != 0)
                    r.rClearQueueTime++;
            /*dequeu right queue*/
            } else {   
                if (getSize(qRight) != 0) {        
                    rArrivalTime = dequeue(&qRight);
                    waitTime = time - rArrivalTime;

                    if (time >= 500) {
                        r.rClearQueueTime++;
                        waitTime += r.rClearQueueTime;
                    }

                    r.rAvgWaitTime += waitTime;
                    if (waitTime > r.rMaxWaitTime)
                        r.rMaxWaitTime = waitTime;
                    r.rTotalVehiclesPassed++;   
                }
                if (time > 500 && getSize(qLeft) != 0)
                    r.lClearQueueTime++;             
            }
        }
	/*light switch at end of lightTime period*/
        if (time < 500) {
            lightSwitch(&lGreen, &rGreen);
            time++;
	/*light switch and increase clear queue time*/
        } else if (getSize(qLeft) != 0 || getSize(qRight) != 0) {
            lightSwitch(&lGreen, &rGreen);
            if (getSize(qLeft) != 0)
	       r.lClearQueueTime++;
	    if (getSize(qRight) != 0)
	       r.rClearQueueTime++;
        }
    }

    /*check for zero, errors may occur*/
    if (r.lTotalVehiclesPassed == 0) {
          r.lAvgWaitTime = 0.0;
          r.lClearQueueTime = 0;
       } else {
          r.lAvgWaitTime = r.lAvgWaitTime / (float)r.lTotalVehiclesPassed;
       }
    if (r.rTotalVehiclesPassed == 0) {
           r.rAvgWaitTime = 0.0;
	   r.rClearQueueTime = 0;
	}
    else
        r.rAvgWaitTime = r.rAvgWaitTime / (float)r.rTotalVehiclesPassed;
    /*    
    free(qLeft);
    free(qRight);
    */  
    return r;
}

/*switch light colours*/
extern void lightSwitch(BOOLEAN *lGreen, BOOLEAN *rGreen) {
    if (*lGreen == TRUE) 
        rightLightGreen(lGreen, rGreen);
    else 
        leftLightGreen(lGreen, rGreen);    
}

/*get random float*/
extern float getRandomChoice() {
   const gsl_rng_type * T;
   gsl_rng * r;
   gsl_rng_env_setup();
   struct timeval tv; 
   gettimeofday(&tv,0);
   unsigned long mySeed = tv.tv_sec + tv.tv_usec;
   T = gsl_rng_default;
   r = gsl_rng_alloc (T);
   gsl_rng_set(r, mySeed);
   double u = gsl_rng_uniform(r);
   gsl_rng_free (r);
   return (float)u;
}
/*round random float to 0 or 1*/
extern int roundNo(float num){
    return num < 0 ? num - 0.5 : num + 0.5;
}

/*make left light green*/
extern void leftLightGreen(BOOLEAN *lGreen, BOOLEAN *rGreen) {
   *lGreen = TRUE;
   *rGreen = FALSE;
}

/*make right light green*/
extern void rightLightGreen (BOOLEAN *lGreen, BOOLEAN *rGreen) {
   *lGreen = FALSE;
   *rGreen = TRUE;
}
