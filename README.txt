README
--------------------------------------------------
Instructions:
- Open linux server (emps-ugcs1)
- Go the the location of the files
- Enter on the command line, ./compileSim
- Enter on the command line, ./runSimulations a b c d 2> err.lis
- Where:
	- a is the left traffic arrival probability, an integer between 0 and 100 inclusive
	- b is the right traffic arrival probability, an integer between 0 and 100 inclusive
	- c is the left traffic light period, an integer greater than 1
	- d is the right traffic light period, an integer greater than 1
- e.g ./runSimulations 50 50 10 10 2> err.lis