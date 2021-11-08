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
Task t;
t.name = name;
t.tid = id;
t.priority = priority;
t.burst = burst
insert_last(&head,t); 
id = id + 1;

}

void schedule() {
    int avg_turn;
    int avg_wait = 0;
    int avg_res;
    struct node *temp;
    temp = head;

    while(temp.next != NULL){
        run(temp->task, temp->task->burst);
        avg_turn = avg_turn + ;
        avg_wait = avg_wait + temp->task->burst;
        avg_res = avg_res;
        temp = temp->next;
    }
}