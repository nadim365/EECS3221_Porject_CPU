#include <stdio.h>
#include <stdlib.h>
#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"
//code to run first come first served scheduling algorithm
struct node *head = NULL;
int id = 0;
//adds tasks into linked list
void add(char *name, int priority, int burst) {
Task *t = NULL;
t->name = name;
t->tid = id;
t->priority = priority;
t->burst = burst;
insert_last(&head,t); 
id = id + 1;

}

void schedule() {
    float avg_turn;
    float avg_wait = 0;
    float avg_res;
    struct node *temp;
    int len = list_len(&head);
    temp = head;

    while(temp->next != NULL){
        run(temp->task, temp->task->burst);
        avg_turn = avg_turn + avg_wait + temp->task->burst;
        avg_wait = avg_wait + temp->task->burst;
        avg_res = avg_wait;
        temp = temp->next;
    }
     avg_turn = avg_turn / ((float) len) ;
     avg_wait = avg_wait / ((float) len) ;
     avg_res = avg_res / ((float) len) ;
     printf("Average waiting time = %f", avg_wait);
     printf("Average turnaround time = %f", avg_turn);
     printf("Average response time = %f", avg_res);
     
}