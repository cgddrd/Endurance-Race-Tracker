/* 
 * File: process.c
 * Description: Provides core functionality when updating and processing 
 * entrants and to predict entrant locations/statuses.
 * 
 * Also includes functionality to detect if an entrant should be excluded 
 * and processing of medical checkpoints.
 * 
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"

/* 
 * Accesses time log file (specified by user input) 
 * and reads in time checkpoint data used to update
 * the location, status and progress of a specific entrant.
 */
int loadTimes() {

    /* Obtain time log FILE pointer returned by openFile (fileIO.c). */
    FILE * time_file = openFile("Enter time file name:");

    if (time_file != NULL) {

        int node, entrant_no, status;
        char time[5];
        char type;

        /* Read file until EOF is reached. */
        while (!feof(time_file)) {

            /* Read in time log information. */
            status = fscanf(time_file, " %c%d%d%s", &type, &node, &entrant_no, time);

            if (status > 0) {
                
                /* Update specific entrant using time log data read in from file. */
                updateEntrant(entrant_list->head, type, node, entrant_no, time);
            }
        }

        fclose(time_file);
        return 1;

    } else {

        /* If an error has occurred, return flag indicating this. */
        return 0;
    }
}

/* 
 * Update current status, location, time and progress of an entrant 
 * using data read in from time log file or manually entered by user.
 */
void updateEntrant(linked_item * current, char type, int node, int entrant, char * time) {

    competitor * temp_competitor = (competitor *) current->data;

    int entrant_updated = 0, i;

     /* 
     * Determine if current entrant item in linked list being
     * accessed matches the entrant ID specified in time log file.
     */
    if (temp_competitor->competitor_number == entrant) {

        /*
         * Perform check to see if this entrant either has already been
         * excluded, or now should be excluded based on the new information.
         */
        if (checkExclusion(temp_competitor, type, node) == 0) {

             /*
              * Perform check to see if new checkpoint is a medical checkpoint.
              * If it is, run specialist function, otherwise continue.
              */
            if (processMedicalCP(temp_competitor, type, node, time) == 0) {

                /* 
                 * Loop through the array of nodes stored in course structure
                 * referenced in current entrant's structure.
                 */
                for (i = 0; i < temp_competitor->course->course_length; i++) {

                    /* 
                     * Check if the current course node ID matches the node ID 
                     * specified in the time log file, and the entrant has not 
                     * already been updated on this occasion.
                     */
                    if (temp_competitor->course->course_nodes[i]->number == node && entrant_updated != 1) {

                        /* 
                         * Check if the array index of the current course node is 
                         * greater than the current progress value of the entrant.
                         * (i.e. prevent the system updating an entrant's location to 
                         * a node index that the entrant has already passed)
                         */
                        if (i > (temp_competitor->current_progress - 1)) {

                            course_node * temp = temp_competitor->course->course_nodes[i];

                            /* Determine the type of the updated node. */
                            if (strcmp(temp_competitor->course->course_nodes[i]->type, "CP") == 0) {

                                temp_competitor->current_status = 1;

                            } else if (strcmp(temp_competitor->course->course_nodes[i]->type, "JN") == 0) {

                                temp_competitor->current_status = 2;

                            }

                            /* Update the entrant's information */
                            temp_competitor->last_logged_node = temp;
                            temp_competitor->current_progress = i + 1;
                            temp_competitor->last_logged_node_index = i;
                            strcpy(temp_competitor->last_logged_time, time);

                            if (temp_competitor->current_progress == 1) {

                                strcpy(temp_competitor->start_time, time);
                            }

                            /* 
                             * Convert new logged time value to integers.
                             * (Used for entrant location prediction)
                             */
                            convertTime(temp_competitor, time);

                            entrant_updated = 1;

                            /* 
                             * Check if the updated location/status/progress of the entrant
                             * now means they have finished their course and 
                             * update accordingly.
                             */
                            if (temp_competitor->current_progress == temp_competitor->course->course_length) {

                                temp_competitor->current_status = 4;

                                strcpy(temp_competitor->finish_time, time);
                            }
                        }
                    }
                }
            }
        }

        /* 
         * Update the location/status of all other entrants
         * in relation to the new current time. 
         */
        updateOtherEntrants(entrant_list->head, current, time);

    } else {

        /* 
         * Otherwise if the current entrant does not match the
         * specified entrant in the time log file data, recursively run the 
         * function again with the next entrant in the linked list.
         */
        if (current->next != NULL) {

            updateEntrant(current->next, type, node, entrant, time);

        } else {

            /* 
             * If no entrants match the specified 
             * entrant number, display error.
             */
            printf("\n\nEntrant cannot be located. Please try again.");
        }
    }

}

/* 
 * Determines whether an entrant has already previously been excluded, 
 * or should now be excluded based on the new data being inputted into
 * the application.
 */
int checkExclusion(competitor * new_competitor, char type, int node) {

    /* If an entrant already has an excluded status */
    if (new_competitor->current_status == 6 || new_competitor->current_status == 7) {

        /* Return entrant excluded flag. */
        return 1;

    } else {

        /* 
         * Search through all course nodes for an ID number that
         * matches the entered checkpoint number.
         */
        linked_item * temp = node_list->head;

        while (temp != NULL) {

            course_node * temp_node = (course_node *) temp->data;
      
            /* 
             * If the log code is an 'I', then the entrant should 
             * be excluded for arriving at an incorrect checkpoint.
             */
            if (type == 'I') {

                new_competitor->current_status = 7;
                new_competitor->last_logged_node = temp_node;
                strcpy(new_competitor->finish_time, "DNF");
                return 1;

            /* 
             * If the log code is an 'E', and the matching node is
             * a medical checkpoint then the entrant should 
             * be excluded for failing a medical check.
             */
            } else if (type == 'E' && strcmp(temp_node->type, "MC") == 0) {

                new_competitor->current_status = 6;
                new_competitor->last_logged_node = temp_node;
                strcpy(new_competitor->finish_time, "DNF");
                return 1;

            }

            temp = temp->next;  
    }
        
    }
        
    /*
     * If the entrant does not fall into any of the above, they should 
     * not be excluded.
     */
    return 0;
}

/* 
 * Determines whether an entrant is arriving, or departing from a 
 * medical checkpoint and updates their information accordingly.
 */
int processMedicalCP(competitor * new_competitor, char type, int node, char * time) {

    /* If an entrant is arriving. */
    if (type == 'A') {

        strcpy(new_competitor->medical_cp_log.last_arrival_time, time);
        
        new_competitor->current_status = 5;

        /* Search through course node linked list for matching node.*/
        linked_item * temp = node_list->head;
        
        while (temp != NULL) {

            course_node * temp_node = (course_node *) temp->data;

            if (temp_node->number == node) {

                /* Update entrant's last logged node.*/
                new_competitor->last_logged_node = temp_node;

            } 
                temp = temp->next;
            
        }

        /* 
         * Loop through all entrant course nodes to locate the index
         * of the latest node (used to calculate current progress)
         */
        int i;
        for (i = 0; i < new_competitor->course->course_length; i++) {

            if (new_competitor->course->course_nodes[i]->number == node 
                    && i > (new_competitor->current_progress) - 1) {

                new_competitor->last_logged_node_index = i;
                new_competitor->current_progress = i + 1;
                break;

            }

        }
        
        return 1;

    /* If an entrant is departing. */
    } else if (type == 'D') {

        int new_delay = 0;
        
        strcpy(new_competitor->medical_cp_log.last_depart_time, time);
        
        /* Calculate the total delay that occurred at the medical checkpoint*/
        new_delay = calcMCDelay(new_competitor->medical_cp_log.last_arrival_time, 
                new_competitor->medical_cp_log.last_depart_time);
        
        /* Increment this new delay onto the total delay time for the entrant. */
        new_competitor->medical_cp_log.total_delay = 
                new_competitor->medical_cp_log.total_delay + new_delay; 
                
        /* Progress the entrant onto the next track. */
        updateCurrentEntrantTrack(new_competitor);
        
        /* Update their status to track.*/
        new_competitor->current_status = 3;

        /* 
         * Return 0 because entrant is allowed to be 
         * automatically progressed now.
         */
        return 0;

    }
    return 0;
}

/* 
 * Calculates the total delay that an entrant 
 * spends at a medical checkpoint.
 */
int calcMCDelay(char * arrive_time, char * depart_time) {

    int arrive_hours, arrive_mins, depart_hours, depart_mins;

    /* 
     * Define subtrings used to hold arrive/depart
     * hour/minute values.
     */
    char * arrive_hours_s = (char*) malloc(2);
    char * arrive_mins_s = (char*) malloc(2);
    char * depart_hours_s = (char*) malloc(2);
    char * depart_mins_s = (char*) malloc(2);

    /* 
     * Extract the hour/minute values from the 
     * arrive/depart time strings.
     */
    strncpy(arrive_hours_s, arrive_time, 2);
    strncpy(arrive_mins_s, arrive_time + 3, 5);
    strncpy(depart_hours_s, depart_time, 2);
    strncpy(depart_mins_s, depart_time + 3, 5);

    /* 
     * Convert these substrings to integers to allow
     * calculations to be performed.
     */
    arrive_hours = atoi(arrive_hours_s);
    arrive_mins = atoi(arrive_mins_s);
    depart_hours = atoi(depart_hours_s);
    depart_mins = atoi(depart_mins_s);
    
    /*
     * Convert all times to minutes.
     */
    int total_arrive_time = (arrive_hours * 60) + (arrive_mins);
    int total_depart_time = (depart_hours * 60) + (depart_mins);
    
    /*
     * Calculate the total delay spent at the medical checkpoint.
     */
    int delay = total_depart_time - total_arrive_time;

    /* Free the memory used by the temporary sub strings.*/
    free(arrive_hours_s);
    free(arrive_mins_s);
    free(depart_hours_s);
    free(depart_mins_s);

    return delay;

}

/* 
 * Convert new entrant time log value to integers to 
 * allow automated entrant location/status prediction to run.
 */
void convertTime(competitor * new_competitor, char * time_string) {

    char *hours = (char*) malloc(2);
    char *mins = (char*) malloc(2);

    /* Specify substrings of time value to obtain hour and minute values.*/
    strncpy(hours, time_string, 2);
    strncpy(mins, time_string + 3, 5);

    new_competitor->last_cp_time.hour = atoi(hours);

    new_competitor->last_cp_time.minutes = atoi(mins);

}

/* 
 * Automatically predict and update location/status of other entrants
 * in relation to new time value obtained from time log file or user input.
 */
void updateOtherEntrants(linked_item * current_item, linked_item * new_item, char * time) {

    competitor * current_competitor = (competitor *) current_item->data;
    competitor * new_competitor = (competitor *) new_item->data;

    /* Ensure the newly updated entrant is not automatically updated again. */
    if (current_competitor->competitor_number != new_competitor->competitor_number) {

        /* 
         * Determine the current entrant's last logged time is not equal 
         * to the newly entered time value.
         * (i.e Do not update the current entrant if they and the newly
         *  updated entrant have arrived at the same time)
         */
        if (strcmp(current_competitor->last_logged_time, time) != 0) {

            /* 
             * If the entrant is currently on either a track or junction
             * progress them onto the next track in their course sequence.
             */
            if (current_competitor->current_status == 1 || 
                    current_competitor->current_status == 2) {

                updateCurrentEntrantTrack(current_competitor);

                current_competitor->current_status = 3;

            } else if (current_competitor->current_status == 3) {

                /* 
                 * Otherwise if an entrant is currently on a track,
                 * determine if they should have completed that track
                 * (using the average time value for that track) and if they
                 * have move them onto the next junction (if applicable).
                 */
                if (checkEntrantCompletedTrack(current_competitor, new_competitor)) {

                    int next_node_index = (current_competitor->last_logged_node_index) + 1;

                    course_node * next_node = current_competitor->course->course_nodes[next_node_index];

                    /* 
                     * If the next node is a junction, progress the entrant onto that junction.
                     * (Entrant cannot be automatically progressed onto a time checkpoint)
                     */
                    if (strcmp(next_node->type, "JN") == 0) {

                        current_competitor->last_logged_node = next_node;
                        current_competitor->current_status = 2;
                        current_competitor->last_logged_node_index = next_node_index;
                        current_competitor->current_progress = current_competitor->current_progress + 1;
                    }

                }

            }

        }

    }

    if (current_item->next != NULL) {

        updateOtherEntrants(current_item->next, new_item, time);

    }
}

/* 
 * Determines the next track that an entrant should progress onto
 * by searching for a track that links the entrant's current, and 
 * next node.
 */
void updateCurrentEntrantTrack(competitor * current_competitor) {

    int node1, node2;

    /* Assign the node ID numbers of the entrant's current, and next scheduled node.*/
    node1 = current_competitor->course->course_nodes[current_competitor->last_logged_node_index]->number;
    node2 = current_competitor->course->course_nodes[(current_competitor->last_logged_node_index) + 1]->number;

    linked_item * temp_item = track_list->head;

    while (temp_item != NULL) {

        course_track * temp_track = (course_track *) temp_item->data;

        /*
         * Check if the currently accessed track has references to the 
         * entrant's current and next node, and if so set this track as 
         * the entrant's current location.
         */
        if ((temp_track->start_node->number == node1 
                && temp_track->end_node->number == node2) || 
                (temp_track->start_node->number == node2 
                && temp_track->end_node->number == node1)) {

            current_competitor->last_logged_track = temp_track;
        }

        temp_item = temp_item->next;

    }

}

/* 
 * Determines whether an entrant should have completed a track based on the average
 * time specified to complete the track and comparing this with the difference between
 * the entrant's last logged time, and the latest time value entered into the system.
 */
int checkEntrantCompletedTrack(competitor * current_competitor, competitor * new_competitor) {

    /* Convert the entrant times to minutes. */
    int new_entrant_time = (new_competitor->last_cp_time.hour * 60) + 
        (new_competitor->last_cp_time.minutes);
    
    int current_entrant_time = (current_competitor->last_cp_time.hour * 60) + 
        (current_competitor->last_cp_time.minutes);

    /* Calculate the time difference in minutes between the two times.*/
    int time_difference = new_entrant_time - current_entrant_time;

     /* 
     * If the time difference between the entrant's last logged time
     * and the current time is greater than the average time required to 
     * complete a track, then the user has completed that track.
     */
    if (time_difference > current_competitor->last_logged_track->minutes) {

        return 1;

    } else {

        return 0;
    }

}

/* 
 * Provides input prompts to allow a user to input a new time log value for a
 * particular entrant.
 */
void userUpdateEntrant(linked_item * entrant, int requested_no) {

    competitor * current_competitor = (competitor *) entrant->data;

    if (current_competitor->competitor_number == requested_no) {

        int node, MC_choice, exc_choice, isMC, checkpoint_exists, exc_reason, i;
        char time[5];
        char log_entry_id;

        printf("\nEnter checkpoint number:\n");
        scanf(" %d", &node);
 
        for (i = 0; i < current_competitor->course->course_length; i++) {

            /* 
             * Determine if the entered checkpoint number exists and if so 
             * is a time checkpoint.
             */
            if (current_competitor->course->course_nodes[i]->number == node 
                    && strcmp(current_competitor->course->course_nodes[i]->type, "CP") == 0) {

                checkpoint_exists = 1;

            /* 
             * Otherwise determine if the entered checkpoint number exists and if so 
             * is a medical checkpoint.
             */
            } else if (current_competitor->course->course_nodes[i]->number == node 
                    && strcmp(current_competitor->course->course_nodes[i]->type, "MC") == 0) {

                checkpoint_exists = 1;
                isMC = 1;
            }
        }

        if (checkpoint_exists == 1) {

            printf("\nEntrant excluded (1 = Yes, 2 = No):\n");
            scanf(" %d", &exc_choice);

            if (exc_choice == 1) {

                printf("\nEntrant reason (1 = Wrong CP, 2 = Failed Medical):\n");
                scanf(" %d", &exc_reason);

                if (exc_reason == 1) {

                    log_entry_id = 'I';

                } else {

                    /* 
                     * If the user tries to exclude an entrant for medical reasons
                     * but the entrant is not at a medical checkpoint, prevent this.
                     */
                    if (isMC != 1) {

                        printf("\nEntered CP not a medical CP. Entrant cannot have failed medical check.");
                        log_entry_id = 'I';

                    } else {

                        log_entry_id = 'E';

                    }
                }

            } else {

                if (isMC == 1) {

                    printf("\nArriving (1), Departing (2):\n");
                    scanf(" %d", &MC_choice);

                    if (MC_choice == 1) {

                        log_entry_id = 'A';

                    } else {
                        
                        log_entry_id = 'D';
                        
                    }

                } else {
                    
                    log_entry_id = 'T';
                    
                }

            }

            printf("\nEnter recorded for checkpoint time (HH:MM):\n");
            scanf(" %s", time);

            updateEntrant(entrant_list->head, log_entry_id, node, requested_no, time);

        } else {
            printf("\nEntered node is not a checkpoint. Please try again.\n");
        }

    } else {

        if (entrant->next != NULL) {

            userUpdateEntrant(entrant->next, requested_no);

        } else {
            printf("\nEntrant cannot be located. Please try again.");
        }
    }
}