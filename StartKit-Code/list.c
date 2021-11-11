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
    struct node *newNode = malloc(sizeof(struct node));
    struct node *last = *head;

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
        printf("[%s] [%d] [%d]\n",temp->task->name, temp->task->priority, temp->task->burst);
        temp = temp->next;
    }
}


int list_len(struct node *head){
    
    struct node *temp;

    temp = head;
    if(temp == NULL){
        return 0;
    }
    else{
        temp = temp->next;
        return 1 + list_len(temp);
    }
}