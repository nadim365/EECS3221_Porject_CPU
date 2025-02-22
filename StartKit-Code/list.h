/**
 * list data structure containing the tasks in the system
 */

#include "task.h"

struct node {
    Task *task;
    struct node *next;
};

// insert and delete operations.
void insert(struct node **head, Task *task);
void insert_last(struct node **head, Task *task);
int list_len(struct node *head);
void delete(struct node **head, Task *task);
void traverse(struct node *head);
void sort_list(struct node *head);
void new_sort_list(struct node *head, int count);
void sort_pr(struct node *head);
void new_sort_pr(struct node *head, int count);