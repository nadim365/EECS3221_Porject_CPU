#include <stdio.h>
#include <stdlib.h>
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

 //insert_arr(&head_1, a);
 insert_last(&head,t);
 id = id + 1;
 counter = counter + 1; 
}



void schedule(){
    float avg_turn = 0.0;
    float avg_wait = 0.0;
    //float wait = 0.0;
    //float turn = 0.0;
    float avg_res = 0.0;
    struct node *temp;
    int looper = max_burst/QUANTUM;
    int len = list_len(head);
    int rem_burst[len];
    int wt[len];
    int i,j;
    int t = 0; //time elapsed

    temp = head;
    //initializing array with burst times of processes
    for(j= 0; j < len; j++)
    {
        rem_burst[j] = temp->task->burst;
        wt[j] = 0;
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
                wt[temp->task->tid] = t - temp->task->burst;
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

    for (i = 0; i < len; i++)
    {
        avg_wait = avg_wait + wt[i];
 
    }
       
    avg_turn = avg_turn / ((float) len) ;
    avg_wait = avg_wait / ((float) len) ;
    avg_res = avg_wait / ((float) len) ;
    printf("Average waiting time = %f \n", avg_wait);
    printf("Average turnaround time = %f \n", avg_turn);
    printf("Average response time = %f \n", avg_res);
     
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
