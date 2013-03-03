/* 
 * File: display.c
 * Description: Provides functionality to display results on screen to user.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"

/* 
 * Determines which entrants have not started on their course yet
 * and prints a list of these entrants to screen. 
 */
void checkNotStarted() {

    linked_item * temp = entrant_list->head;

    int count = 0;

    printf("\n|  Competitor No   |"
            "                      Competitor Name                   |"
            "   Current Status  |");
    
    printf("\n|==================|"
            "========================================================|"
            "===================|");

    while (temp != NULL) {

        competitor * current_competitor = (competitor *) temp->data;

        /* Determine if current entrant status is NOTSTARTED. */
        if (current_competitor->current_status == 0) {

            char status[12];

            switch (current_competitor->current_status) {

                case 0:
                    strcpy(status, "Not Started");
                    break;
                default:
                    strcpy(status, "Unknown");
                    break;
            }

            printf("\n| %8d         |   %-50s   |    %-12s   |", current_competitor->competitor_number, current_competitor->name, status);
            printf("\n|------------------|"
                    "--------------------------------------------------------|"
                    "-------------------|");

            count++;

        }
        temp = temp->next;
    }

    if (count == 0) {
        printf("\n\nAll competitors have started.\n");
    } else {
        printf("\n\nTotal competitors yet to start: %d\n", count);
    }

}

/* 
 * Determines which entrants are currently on their designated course
 * and prints a list of these entrants to screen. 
 */
void checkStarted() {

    linked_item * temp = entrant_list->head;

    int count = 0;

    printf("\n|  Competitor No   |"
            "                      Competitor Name                   |"
            "   Current Status  |");
    
    printf("\n|==================|"
            "========================================================|"
            "===================|");

    while (temp != NULL) {

        competitor * current_competitor = (competitor *) temp->data;

        if (current_competitor->current_status == 1 ||
                current_competitor->current_status == 2 ||
                current_competitor->current_status == 3) {

            char status[12];

            /* Determine current entrant status 
             * and output required status string
             */
            switch (current_competitor->current_status) {

                case 1:
                    sprintf(status, "Checkpoint %d", current_competitor->last_logged_node->number);
                    break;
                case 2:
                    sprintf(status, "Junction %d", current_competitor->last_logged_node->number);
                    break;
                case 3:
                    sprintf(status, "Track %d", current_competitor->last_logged_track->number);
                    break;
                default:
                    strcpy(status, "Unknown");
                    break;
            }

            printf("\n| %8d         |   %-50s   |    %-12s   |",
                    current_competitor->competitor_number,
                    current_competitor->name, status);

            printf("\n|------------------|"
                    "--------------------------------------------------------|"
                    "-------------------|");

            count++;

        }

        temp = temp->next;
    }

    if (count == 0) {
        printf("\n\nNo competitors are currently on the course\n");
    } else {
        printf("\n\nTotal competitors out on course: %d\n", count);
    }

}

/* 
 * Determines which entrants have finished their course
 * and prints a list of these entrants to screen. 
 */
void checkFinished() {

    linked_item * temp = entrant_list->head;

    int count = 0;

    printf("\n|  Competitor No   |"
            "                      Competitor Name                   |"
            "   Current Status  |");
    
    printf("\n|==================|"
            "========================================================|"
            "===================|");

    while (temp != NULL) {

        competitor * current_competitor = (competitor *) temp->data;

        /* Determine if current entrant status is FINISHED. */
        if (current_competitor->current_status == 4) {

            char status[12];

            switch (current_competitor->current_status) {

                case 4:
                    strcpy(status, "Finished");
                    break;
                default:
                    strcpy(status, "Unknown");
                    break;
            }

            printf("\n| %8d         |   %-50s   |    %-12s   |", 
                    current_competitor->competitor_number,
                    current_competitor->name, 
                    status);
            
            printf("\n|------------------|"
                    "--------------------------------------------------------|"
                    "-------------------|");

            count++;

        }
        temp = temp->next;
    }

    if (count == 0) {
        printf("\nNo competitors have currently finished.\n");

    } else {
        printf("\nTotal competitors finished: %d\n", count);
    }
}

/* 
 * Determines which entrants have been excluded from their course. 
 */
void checkExcluded() {

    linked_item * temp = entrant_list->head;

    int count = 0;

    printf("\n|  Competitor No   |"
            "                      Competitor Name                   |"
            "   Current Status  |");
    
    printf("\n|==================|"
            "========================================================|"
            "===================|");

    while (temp != NULL) {

        competitor * current_competitor = (competitor *) temp->data;

        /* Determine if current entrant status is FINISHED. */
        if (current_competitor->current_status == 6 
                || current_competitor->current_status == 7) {

            char status[12];

            switch (current_competitor->current_status) {

                case 6:
                    strcpy(status, "Excluded-MC");
                    break;
                case 7:
                    strcpy(status, "Excluded-IR");
                    break;
                default:
                    strcpy(status, "Unknown");
                    break;
            }

            printf("\n| %8d         |   %-50s   |    %-12s   |", 
                    current_competitor->competitor_number,
                    current_competitor->name, 
                    status);
            
            printf("\n|------------------|"
                    "--------------------------------------------------------|"
                    "-------------------|");

            count++;

        }
        temp = temp->next;
    }

    if (count == 0) {
        printf("\nNo competitors have currently been excluded.\n");

    } else {
        printf("\nTotal competitors excluded: %d\n", count);
    }
}

/* 
 * Display complete results list for event including all entrants.
 * (Including entrant name, status, start time, and end time)
 */
void displayResultsList() {

    linked_item * temp = entrant_list->head;

    printf("\n| Comp. No |                     Competitor Name                    |"
            "    Current Status    |"
            "   Start Time  |"
            "   End Time  |"
            "   Delay  |");
    
    printf("\n|==========|========================================================|"
            "======================|"
            "===============|"
            "=============|"
            "==========|");

    while (temp != NULL) {

        competitor * current_competitor = (competitor *) temp->data;

        char status[12];
        char delay[10];

        switch (current_competitor->current_status) {

            case 0:
                strcpy(status, "Not Started");
                break;
            case 1:
                sprintf(status, "Checkpoint %d", current_competitor->last_logged_node->number);
                break;
            case 2:
                sprintf(status, "Junction %d", current_competitor->last_logged_node->number);
                break;
            case 3:
                sprintf(status, "Track %d", current_competitor->last_logged_track->number);
                break;
            case 4:
                strcpy(status, "Finished");
                break;
            case 5:
                sprintf(status, "Medical CP %d", current_competitor->last_logged_node->number);
                break;
            case 6:
                strcpy(status, "Excluded - MC");
                break;
            case 7:
                strcpy(status, "Excluded - IR");
                break;
            default:
                strcpy(status, "Unknown");
                break;
        }

        sprintf(delay, "%d mins", current_competitor->medical_cp_log.total_delay);

        printf("\n|   %-4d   |   %-50s   |    %-15s   |      %-5s    |    %-5s    |  %-6s  |",

                current_competitor->competitor_number,
                current_competitor->name,
                status,
                current_competitor->start_time,
                current_competitor->finish_time,
                delay);

        printf("\n|----------|"
                "--------------------------------------------------------|"
                "----------------------|"
                "---------------|-------------|----------|");
        temp = temp->next;
    }
}