//    Final Project COMP 310
//    Your Name: Saksham Mungroo
//    Your McGill ID: 260768072
//
//    You need to fill in this file for the third problem
//

#include "DISK_driver.h"
#include "DISK_driver_problem1.h"
#include "DISK_driver_problem2.h"
#include "DISK_driver_problem3.h"


int seek_EXAM(int AFTid, int offset){
	if(active_file_table[AFTid] == NULL){
		printf("%s\n", "The file at position AFTid is not opened");
		return -1;
	}
	FILE *f = active_file_table[AFTid];
	int upperBound = fat[active_file_table_owners[AFTid]].blockPtrs[0];
	if(upperBound == -1){
		printf("%s\n", "File is empty!");
		return -1;
	}
	int lowerBound = 0;
	int x = 1;
	while(fat[active_file_table_owners[AFTid]].blockPtrs[x] != -1){
		lowerBound++;
		x++;
	}
	int count = 0;
	int increment = 1;
	if(offset < 0){
		increment = -1;
	}
	fseekToBlock(f, upperBound);
	while(count != offset){
		if(count % currentPartition.block_size == 0){
			fat[active_file_table_owners[AFTid]].current_location += increment;
			if(fat[active_file_table_owners[AFTid]].current_location > lowerBound){
				fat[active_file_table_owners[AFTid]].current_location -= increment;
				f -= increment;
				printf("ERROR: Out of bounds. Stopped at end of file");
				return -1;
			}
			else if(fat[active_file_table_owners[AFTid]].current_location < 0){
				fat[active_file_table_owners[AFTid]].current_location -= increment;
                                f -= increment;
                                printf("ERROR: Out of bounds. Stopped at start of file");
				return -1;
                        }

		}
		fseek(f, increment, SEEK_CUR);
		count += increment;
		//printf("count = %d\n", count);
	}
	return 0;
}
