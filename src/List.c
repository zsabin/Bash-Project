//call in all the necessary libraries

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "List.h"

void removeLast(List *list) {
    Node *head = list->head;
    
    //if singleton, just remove it
    if (head->next == NULL) {
        free(head);
        return;
    }

    //get the last node
    Node *current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    
    //points at the last item
    //remove current->next
    free(current->next);
    current->next = NULL;
}

void removeFirst(List *list) {
    Node *head = list->head;
    Node *next_node = NULL;

    if (head == NULL) {
        return;
    }

    next_node = head->next;
    free(head);
    list->head = next_node;
}

void removeNode(List *list, int n) {
    int i = 0;
    Node *current = list->head;
    Node *temp_node = NULL;

    if (n == 0) {
        return removeFirst(list);
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

void print_list(List *list) {
    Node *current = list->head;

    printf("[");
    while (current != NULL) {
        printf("%s", current->value);
        if (current->next) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]");
}

void pushToFront(List *list, char *value) {
    Node *new_node = malloc(sizeof(Node));

    strcpy(new_node->value, value);
    new_node->next = list->head;
    
    list->head = new_node;
}

void pushToEnd(List *list, char *value) {
    Node *current = list->head;
    
    Node *node = malloc(sizeof(Node));
    strcpy(node->value, value);
    node->next = NULL;
    
    while (current->next != NULL) {
        current = current->next;
    }

    //add on the variable
    if (current) {
        current->next = node;
    } else {
        list->head = node;
    }
}

void addElement(List *list, char *value) {
    //Add Node to front of list
    Node *head = list->head;
    if (!head || strcasecmp(value, head->value) <= 0) {
        pushToFront(list, value);
        return;
    }
   
    Node *current = head;
    Node *next = current->next;
    while (next && strcasecmp(value, next->value) > 0) {
        current = next;
        next = next->next;
    }
    
    //Add Node to end of list
    if (!next && strcasecmp(value, current->value) > 0) {
        pushToEnd(list, value);
        return;
    }
    
    //Create and insert Node
    Node *node = malloc(sizeof(Node));
    strcpy(node->value, value);

    current->next = node;
    node->next = next;
}

List * create_list() {
    List *list = malloc(sizeof(List));
    list->head = NULL;
    return list;
}