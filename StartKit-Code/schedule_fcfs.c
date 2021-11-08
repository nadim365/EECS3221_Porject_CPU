#include <stdio.h>
#include <stdlib.h>
#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"
//code to run first come first served scheduling algorithm
struct node *head = NULL;

//adds tasks into linked list
void add(char *name, int priority, int burst) {
Task t;
t.name = name;
//t.tid =
t.priority = priority;
t.burst = burst
insert(&head,t); 

}

void schedule() {
    int turnaroundTime;
    int waitTime;
    int responseTime;
    struct node *temp;
    temp = head;

    while(temp.next != NULL){
        run(temp->task, temp->task->burst);
    }
}