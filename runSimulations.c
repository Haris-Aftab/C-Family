#include "runSimulations.h"

/*main function*/
int main(int argc, char **argv) {
   RESULTS r;
   int i, j;
   float lTotalVehiclesPassed = 0.0, rTotalVehiclesPassed = 0.0;
   float lAvgWaitTime = 0.0, rAvgWaitTime = 0.0;
   float lMaxWaitTime = 0.0, rMaxWaitTime = 0.0;
   float lClearQueueTime = 0.0, rClearQueueTime = 0.0;
   
   /*user input error handling*/ 
   if (argc != 5) {
      fprintf(stderr, "Invalid amount of paramaters passed.\nPlease enter 4 integers.\n");
      exit(-1);
   }
   
   
   if (atoi(argv[1]) > 100 || atoi(argv[2]) > 100) {
      fprintf(stderr, "Traffic light period must be between 0 and 100.\nPlease enter 4 integers.\n");
      exit(-1);
   }
 

   if (atoi(argv[3]) <= 1 || atoi(argv[4]) <= 1) {
      fprintf(stderr, "Traffic light period must be great than one.\nPlease enter 4 integers.\n");
      exit(-1);      
   }  

   for (i = 1; i < argc; i++)  {
      for (j = 0; j<(int)strlen(argv[i]); j++) {
         if (!isdigit(argv[i][j])) {
	    fprintf(stderr, "Invalid parameters passed. Please enter 4 integers!\n");
	    exit(-1);
	 }
      }
   }
   /*store users parameters*/
   int lArriveRate = atoi(argv[1]);
   int rArriveRate = atoi(argv[2]);
   int lGreenTime = atoi(argv[3]);
   int rGreenTime = atoi(argv[4]);
   /*get average values over 100 iterations*/
   for (i=0; i < 100; i++) {
      /*r = runOneSimulation(50,50,3,3);*/
      r = runOneSimulation(lArriveRate, rArriveRate, lGreenTime, rGreenTime);

      lTotalVehiclesPassed += (float)r.lTotalVehiclesPassed;
      rTotalVehiclesPassed += (float)r.rTotalVehiclesPassed;
      lAvgWaitTime += r.lAvgWaitTime;
      rAvgWaitTime += r.rAvgWaitTime;
      lMaxWaitTime += (float)r.lMaxWaitTime;
      rMaxWaitTime += (float)r.rMaxWaitTime;
      lClearQueueTime += (float)r.lClearQueueTime;
      rClearQueueTime += (float)r.rClearQueueTime;
   }

   lTotalVehiclesPassed /= 100;
   rTotalVehiclesPassed /= 100;
   lAvgWaitTime /= 100;
   rAvgWaitTime /= 100;
   lMaxWaitTime /= 100;
   rMaxWaitTime /= 100;
   lClearQueueTime /= 100;
   rClearQueueTime /= 100;

   printf("Parameter values: \n");
   printf("\tfrom left: \n");
   printf("\t\ttraffic arrival rate: %d\n", lArriveRate);
   printf("\t\ttraffic light period: %d\n", lGreenTime);
   printf("\tfrom right: \n");
   printf("\t\ttraffic arrival rate: %d\n", rArriveRate);
   printf("\t\ttraffic light period: %d\n", rGreenTime);

   printf("Results (averaged over 100 runs): \n");
   printf("\tfrom left: \n");
   printf("\t\tnumber of vehicles:   %.2f\n", lTotalVehiclesPassed);
   printf("\t\taverage waiting time: %.2f\n", lAvgWaitTime);
   printf("\t\tmaximum waiting time: %.2f\n", lMaxWaitTime);
   printf("\t\tclearance time:       %.2f\n", lClearQueueTime);
   printf("\tfrom right: \n");
   printf("\t\tnumber of vehicles:   %.2f\n", rTotalVehiclesPassed);
   printf("\t\taverage waiting time: %.2f\n", rAvgWaitTime);
   printf("\t\tmaximum waiting time: %.2f\n", rMaxWaitTime);
   printf("\t\tclearance time:       %.2f\n", rClearQueueTime);


   return 0; 
}
