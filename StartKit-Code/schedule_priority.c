#include <stdio.h>
#include <stdlib.h>
#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"

//code to run shortest job first scheduling algorithm
struct node *head = NULL;
int id = 0;
int counter = 0;

//adds tasks into linked list
void add(char *name, int priority, int burst) {
Task *t = malloc(sizeof(struct task)) ;
t->name = name;
t->tid = id;
t->priority = priority;
t->burst = burst;
insert(&head,t);
id = id + 1;
counter = counter + 1; 
}

void schedule(){
    float avg_turn = 0.0;
    float avg_wait = 0.0;
    float avg_res = 0.0;
    float wait = 0.0;
    struct node *temp;
    int len = list_len(head);
    
    new_sort_pr(head,counter); //sort tasks by priority,  ascending
    temp = head;
    
    while(temp != NULL){
        run(temp->task, temp->task->burst);
        
        avg_turn = avg_turn + avg_wait + temp->task->burst;
        wait = wait + avg_wait;
        avg_wait = avg_wait + temp->task->burst;
        avg_res = avg_wait;
        temp = temp->next;
    }

    avg_turn = avg_turn / ((float) len) ;
    avg_wait = wait / ((float) len) ;
    avg_res = wait / ((float) len) ;
    
    printf("Average waiting time = %.2f \n", avg_wait);
    printf("Average turnaround time = %.2f \n", avg_turn);
    printf("Average response time = %.2f \n", avg_res);
}