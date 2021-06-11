//    Final Project COMP 310
//    Your Name: Saksham Mungroo
//    Your McGill ID: 260768072
//
//    You need to fill in this file for the fourth random problem



//	  Fill in the name of the command that you are implementing here 
//    ------------------>chmod_EXAM<-----------------------------

#include "DISK_driver.h"
#include "DISK_driver_problem1.h"
#include "DISK_driver_problem2.h"
#include "DISK_driver_problem3.h"
#include "DISK_driver_problem4.h"


int chmod_EXAM(int AFTid, int readP, int writeP){
	if(AFTid >= MAX_OPENFILES){
                printf("%s\n", "Please input an active_file_table_id between 0 and 49");
                return -1;
        }
	if(active_file_table_owners[AFTid] == -1){
		printf("There is no file associated with this active file table id");
		return -1;
	}
	if(readP == 0 || readP == 1){
		fat[active_file_table_owners[AFTid]].read = readP;
	}
	if(writeP == 0 || writeP == 1){
		fat[active_file_table_owners[AFTid]].write = writeP;
	}
	return 0;
}
