//call in all the necessary libraries

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "List.h"

void removeLast(List *head) {
    //if singleton, just remove it
    if (head->next == NULL) {
        free(head);
    }

    //get the last node
    List *current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    
	//points at the last item
	//remove current->next
    free(current->next);
    current->next = NULL;
}

void removeFirst(List **head) {
    List *next_node = NULL;

    if (*head == NULL) {
        return;
    }

    next_node = (*head)->next;
    free(*head);
    *head = next_node;
}

void removeNode(List **head, int n) {
    int i = 0;
    List *current = *head;
    List *temp_node = NULL;

    if (n == 0) {
        return removeFirst(head);
    }

    for (int i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return;
        }
        current = current->next;
    }

    temp_node = current->next;
    current->next = temp_node->next;
    free(temp_node);
}

void print_list(List *head) {
    List *current = head;

    while (current != NULL) {
        printf("%d\n", current->value);
        current = current->next;
    }
}

void pushToFront(List **head, char *value) {
    List *new_node;
    new_node = malloc(sizeof(List));

    strcpy(new_node->value, value);
    new_node->next = *head;
    *head = new_node;
}

void pushToEnd(List *head, char *value) {
    List *current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    //add on the variable
    current->next = malloc(sizeof(List));
    strcpy(current->next->value, value);
    current->next->next = NULL;
}