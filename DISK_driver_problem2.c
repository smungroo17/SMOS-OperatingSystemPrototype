//    Final Project COMP 310
//    Your Name: Saksham Mungroo
//    Your McGill ID: 260768072
//
//    You need to fill in this file for the second problem
//

#include "DISK_driver.h"
#include "DISK_driver_problem1.h"
#include "DISK_driver_problem2.h"

int close_EXAM(int AFTid){
        if(active_file_table[AFTid] == NULL && active_file_table_owners[AFTid] == -1){
                printf("ERROR: Index number not in use\n");
                return -1;
        }
        fclose(active_file_table[AFTid]);
        active_file_table[AFTid] = NULL;
        fat[active_file_table_owners[AFTid]].current_location = 0;
        active_file_table_owners[AFTid] = -1;
        return 0;
}

