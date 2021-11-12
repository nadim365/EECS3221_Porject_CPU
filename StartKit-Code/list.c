/**
 * Various list operations
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "task.h"


// add a new task to the list of tasks
void insert(struct node **head, Task *newTask) {
    // add the new task to the list 
    struct node *newNode = malloc(sizeof(struct node));

    newNode->task = newTask;
    newNode->next = *head;
    *head = newNode;
}

//adding a node at the end of the list
void insert_last(struct node **head, Task *newTask){

    //allocate memory to store the task
    struct node *newNode = malloc(sizeof(struct node));
    struct node *last = *head;
    
    //initialize task to be added
    newNode->task = newTask;
    newNode->next = NULL;

    //if list is empty
    if(*head == NULL)  {
        *head = newNode;
        return;
    } 

    // if list is not empty then goto last node at end of list
    while(last->next != NULL){
        last = last->next;
    }
    
    //make the previous last node point to new last node
    last->next = newNode;

}

// delete the selected task from the list
void delete(struct node **head, Task *task) {
    struct node *temp;
    struct node *prev;

    temp = *head;
    // special case - beginning of list
    if (strcmp(task->name,temp->task->name) == 0) {
        *head = (*head)->next;
    }
    else {
        // interior or last element in the list
        prev = *head;
        temp = temp->next;
        while (strcmp(task->name,temp->task->name) != 0) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = temp->next;
    }
}

// traverse the list
void traverse(struct node *head) {
    struct node *temp;
    temp = head;

    while (temp != NULL) {
        printf("[%s] [%d] [%d] [%d]\n",temp->task->name, temp->task->priority, temp->task->burst, temp->task->tid);
        temp = temp->next;
    }
}

//function to return the length of the linked list
int list_len(struct node *head){
    
    //initialize temporary variable
    struct node *temp;

    temp = head;

    //base case : when we reach last node
    if(temp == NULL){
        return 0;
    }
    else{
        temp = temp->next;
        //recursively call the function till we reach the last node
        return 1 + list_len(temp);
    }
}


void sort_list(struct node *head)
{
    struct node *curr = NULL;
    struct node *temp = NULL;
    
    Task *t = malloc(sizeof(struct task));

    curr = head;
    
    while(curr != NULL)
    {
        
        temp = curr;

        while(temp->next != NULL)
        {

            if(temp->task->burst >= temp->next->task->burst)
            {
                t = temp->task;
                temp->task = temp->next->task;
                temp->next->task = t;
            }
            
            temp = temp->next;
        }
        curr = curr->next;
    }

}