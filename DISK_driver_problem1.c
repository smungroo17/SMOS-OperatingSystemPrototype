//    Final Project COMP 310
//    Your Name: Saksham Mungroo
//    Your McGill ID: 260768072
//
//    You need to fill in this file for the first problem
//

#include <string.h>
#include <stdlib.h>

#include "DISK_driver.h"
#include "DISK_driver_problem1.h"

char* read_EXAM(int AFTid, char *var, int count){
	if(AFTid >= MAX_OPENFILES){
                printf("%s\n", "Please input an active_file_table_id between 0 and 49");
                return NULL;
        }
        if(active_file_table[AFTid] == NULL){
                printf("%s\n", "ERROR: Open the file first.");
                return NULL;
        }
        if(fat[active_file_table_owners[AFTid]].current_location > MAX_BLOCKS){
                return NULL;
        }
	if(fat[active_file_table_owners[AFTid]].read == 0){
		printf("ERROR: Read permission denied.\n");
		return NULL;
	}
        if(fat[active_file_table_owners[AFTid]].blockPtrs[0] == -1){
                printf("File is empty");
                return NULL;
        }
        FILE *f = active_file_table[AFTid];
        fseekToBlock(f, fat[active_file_table_owners[AFTid]].blockPtrs[count]);
	int i = 0;
        for (; i < currentPartition.block_size; i++) {
                char c = fgetc(f);
                if(c == '0'){
                        blockBuffer[i] = '\0';
                        break;
                }
                blockBuffer[i] = c;
        }
        blockBuffer[i] = '\0';
        return blockBuffer;
}

void update_data_structures_and_DISK(int AFTid){
        fat[active_file_table_owners[AFTid]].blockPtrs[fat[active_file_table_owners[AFTid]].current_location] = currentPartition.last_free_block;
        currentPartition.last_free_block += 1;
        fat[active_file_table_owners[AFTid]].current_location += 1;
        fat[active_file_table_owners[AFTid]].file_length +=1;
        if(fat[active_file_table_owners[AFTid]].current_location < MAX_BLOCKS)
                fat[active_file_table_owners[AFTid]].blockPtrs[fat[active_file_table_owners[AFTid]].current_location] = -1;
        FILE *partitionFile = fopen(filenameCpy, "r+");
        updateFATOnDisk();
        fclose(partitionFile);

}

int write_EXAM(int AFTid, char *data){
	if(AFTid >= MAX_OPENFILES){
                printf("%s\n", "Please input an active_file_table_id between 0 and 49");
                return -1;
        }
        if(active_file_table[AFTid] == NULL){
                printf("%s\n", "ERROR: Open the file first.");
                return -1;
        }
        if(fat[active_file_table_owners[AFTid]].current_location > MAX_BLOCKS){
                printf("%s\n", "File data portion is full! No more space.");
		return -1;
        }
	if(fat[active_file_table_owners[AFTid]].write == 0){
		printf("ERROR: Write permission deied.\n");
	}
	FILE *filePtr = active_file_table[AFTid];

    	fseekToNextFreeBlock(filePtr);

    	for (int i = 0; i < currentPartition.block_size; i++) {
        	char c = *(data+i);
        	if(c == 0)
            		c = '0';
        	fputc(c, filePtr);
    	}
	update_data_structures_and_DISK(AFTid);
	return 1;	
}

int open_EXAM(int AFTid, char *fileToOpen){
        if(AFTid >= MAX_OPENFILES){
                printf("%s\n", "Please input an active_file_table_id between 0 and 49");
                return -1;
        }
        else if(active_file_table[AFTid] != NULL){
                printf("%s\n", "ERROR: Index number in use");
                return -1;
        }

        else{
                int fat_index = 0;
                for(fat_index = 0; fat_index < MAX_FILES; fat_index++){
                        if(fat[fat_index].filename != NULL && strcmp(fat[fat_index].filename, fileToOpen) == 0){
                                for(int j = 0; j < MAX_OPENFILES; j++){
                                        if(active_file_table_owners[j] == fat_index){
                                                printf("%s\n", "File is already opened!");
                                                return fat_index;
                                        }
                                }
                                fat[fat_index].current_location = 0;
                                break;
                        }
                        else if(fat[fat_index].filename == NULL){
                                fat[fat_index].filename = malloc(sizeof(500));
                                strcpy(fat[fat_index].filename, fileToOpen);
                                fat[fat_index].current_location = 0;
                                fat[fat_index].file_length = 0;
                                break;
                        }
                }
                active_file_table_owners[AFTid] = fat_index;
                active_file_table[AFTid] = fopen(filenameCpy, "r+");
                return fat_index;
        }
}
