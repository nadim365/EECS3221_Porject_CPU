#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"


//code to run priority round robin scheduling algorithm
struct node *head = NULL;
int id = 0;
int counter = 0;//variable used in sort function
int max_burst = 0;
int pr[11]; //array contains number of process for each priority



//adds tasks into linked list
void add(char *name, int priority, int burst){
 Task *t = malloc(sizeof(struct task));
 t->name = name;
 t->tid = id;
 t->priority = priority;
 t->burst = burst;
pr[priority] = pr[priority] + 1;

 if (max_burst < burst)
 {
     max_burst = burst;
 }

 //insert_arr(&head_1, a);
 insert_last(&head,t);
 id = id + 1;
 counter = counter + 1; 
}



void schedule(){
    float avg_turn = 0.0;
    float avg_wait = 0.0;
    float avg_res = 0.0;
    struct node *temp;
    int looper = max_burst/QUANTUM;
    int len = list_len(head);
    bool res[len];
    int burst[len];
    int wt[len];
    int wait = 0;
    int i,j;
    int t = 0; //time elapsed
    pr[0] = 0;
    new_sort_pr(head, counter);
   temp = head;
    //initializing array with burst times of processes
    for(j= 0; j < len; j++)
    {
        burst[j] = temp->task->burst;
        wt[j] = 0;
        res[j] = false;
        temp = temp->next; 
    }
    
    temp = head;
    for (i = 10; i >= 1; i--)
    {   //iterate for every priority
        for (j = 0; j < looper; j++)
        {  //runnning round robin on task list
            temp = head;
            while(temp != NULL)
           {
             if (temp->task->priority == i && pr[i] == 1)
               { // if process is only one having the current priority run as is 
                 run(temp->task, temp->task->burst);
                 t = t + temp->task->burst;
                 wt[temp->task->tid] = t - burst[temp->task->tid];
                  if (res[temp->task->tid] == false)
                   {
                     avg_res = avg_res + t - temp->task->burst;
                     res[temp->task->tid] = true;
                    }
                temp->task->burst = 0;
                delete(&head, temp->task);
               }
             if (temp->task->priority == i && pr[i] > 1)
             { //if there are more than 1 process with same priority run then in round robin
                  if (temp->task->burst > QUANTUM)//process just starts execution
                  {
                     run(temp->task, QUANTUM);
                     t = t + QUANTUM;
                     temp->task->burst = temp->task->burst - QUANTUM;
                     if (res[temp->task->tid] == false)
                     {
                         avg_res = avg_res + t - QUANTUM;
                         res[temp->task->tid] = true;
                     }
                  }
                 else
                  { //process is at last stage of execution
                     if(temp->task->burst <= QUANTUM)
                      {
                         if (temp->task->burst != 0)
                          {
                              run(temp->task, temp->task->burst);
                              if (res[temp->task->tid] == false)
                              {
                                  avg_res = avg_res + t ;
                                  res[temp->task->tid] = true;
                               }
                              t = t + temp->task->burst;
                             wt[temp->task->tid] = t - burst[temp->task->tid];
                             temp->task->burst = 0; //process finished, set burst to 0 
                           }
                      }
                   }
                 
               }
               temp = temp->next;
           }
        }
    }
    avg_wait = avg_wait + wait;
    //summing up the wait times and adding burst times to avg_turn 
    for (i = 0; i < len; i++)
    {
        avg_wait = avg_wait + wt[i];
        avg_turn = avg_turn + burst[i];
    }
    avg_turn = avg_turn + avg_wait; //adding wait time to turnaround time

    avg_turn = avg_turn / ((float) len) ;
    avg_wait = avg_wait / ((float) len) ;
    avg_res = avg_res / ((float) len) ;
    printf("time = %d \n", t);
    printf("Average waiting time = %.2f \n", avg_wait);
    printf("Average turnaround time = %.2f \n", avg_turn);
    printf("Average response time = %.2f \n", avg_res);
     
}
