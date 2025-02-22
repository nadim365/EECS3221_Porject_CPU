#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"


//code to run round robin scheduling algorithm
struct node *head = NULL;
int id = 0;
int counter = 0;
int max_burst = 0; 


//adds tasks into linked list
void add(char *name, int priority, int burst){
 Task *t = malloc(sizeof(struct task));
 t->name = name;
 t->tid = id;
 t->priority = priority;
 t->burst = burst;


 if (max_burst < burst)
 {
     max_burst = burst;
 }

 
 insert_last(&head,t);
 id = id + 1;
 counter = counter + 1; 
}



void schedule(){
    float avg_turn = 0.0;
    float avg_wait = 0.0;
    float avg_res = 0.0;
    struct node *temp;
    int looper = max_burst/QUANTUM; //determines how many times for loop should run
    int len = list_len(head);
    bool res[len]; //array to keep track if response time is calculated for that process
    int burst[len]; //array containing original burt times of tasks
    int wt[len]; //array to hold wait time of each process
    int i,j;
    int t = 0; //time elapsed, maintains CPU time

    temp = head;
    //initializing array with burst times of processes
    //initializing array for wait time to 0
    //initializing array for response time to false
    for(j= 0; j < len; j++)
    {
        burst[j] = temp->task->burst;
        wt[j] = 0;
        res[j] = false;
        temp = temp->next; 
    }
    
    
    for(i = 0; i < looper ; i++)
    {
        temp = head;

        while(temp != NULL)
        {
            //process starts execution
           if (temp->task->burst > QUANTUM)
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
                       temp->task->burst = 0; //process finished, set burst to 0 as a result
                       
                   }
               }
           }
         temp = temp->next;
      }
    }

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

/*
void schedule(){
    float avg_turn = 0.0;
    float avg_wait = 0.0;
    float wait = 0.0;
    float turn = 0.0;
    float avg_res = 0.0;
    struct node *temp;
    int looper = max_burst/QUANTUM;
    int len = list_len(head);
    int rem_burst[len];
    int i,j;
    int t = 0; //time elapsed

    temp = head;
    //initializing array with burst times of processes
    for(j= 0; j < len; j++)
    {
        rem_burst[j] = temp->task->burst;
        temp = temp->next; 
    }
    
    
    for(i = 0; i < looper ; i++)
    {

        temp = head;

        while(temp != NULL)
        {
           //last stage of process
            if ( (rem_burst[temp->task->tid] > 0) && (rem_burst[temp->task->tid] < QUANTUM) )
            {
                
                
                run(temp->task, rem_burst[temp->task->tid]);
                //rem_burst[temp->task->tid] = 0;
                t = t + rem_burst[temp->task->tid];
                  //wait = t - temp->task->burst;
                //turn = wait + temp->task->burst;
                //avg_turn = avg_turn + temp->task->burst + wait;
                //avg_turn = avg_turn + turn;
                
                
                //avg_wait = avg_wait + wait;
                rem_burst[temp->task->tid] = 0;
                

            }
            //process finished executing
            else if (rem_burst[temp->task->tid] == 0 || rem_burst[temp->task->tid] < 0)
            {
                //t = t + rem_burst[temp->task->tid];
                //wait = t - temp->task->burst;
                //avg_turn = avg_turn + temp->task->burst + wait;
                //avg_wait = avg_wait + wait;
                //wait = t - temp->task->burst;
                //avg_wait = wait + avg_wait;
                turn = t + temp->task->burst;
                avg_turn = avg_turn + turn;
                wait = t - temp->task->burst;
                avg_wait = avg_wait + wait;
                temp = temp->next;
                continue;
            }
            //process has just started executing
            else{
                //printf("third if \n");
                run(temp->task, rem_burst[temp->task->tid]);
                t = t + QUANTUM;
                rem_burst[temp->task->tid] = rem_burst[temp->task->tid] - QUANTUM;
            }

         //avg_wait = avg_wait + (avg_turn + temp->task->burst);
         //avg_turn = avg_turn + avg_wait + temp->task->burst;
         //wait = wait + avg_wait;
         //avg_wait = avg_wait + wait;
         avg_res = avg_wait;
         temp = temp->next;
      }
    }
       
    avg_turn = avg_turn / ((float) len) ;
    avg_wait = avg_wait / ((float) len) ;
    avg_res = wait / ((float) len) ;
    printf("Average waiting time = %f \n", avg_wait);
    printf("Average turnaround time = %f \n", avg_turn);
    printf("Average response time = %f \n", avg_res);
     
}
*/
