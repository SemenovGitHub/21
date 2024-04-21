#include "list.h"
#include <stdlib.h>

#ifndef LIST_H
#define LIST_H

typedef struct door {
    int id;
    int status;
} door;

typedef struct node {
    door data;
    struct node *next;
} node;

node* init(door* door);
node* add_door(node* elem, door* door);
node* find_door(int door_id, node* root);
node* remove_door(node* elem, node* root);
void destroy(node* root);

#endif


node* init(door* door) {
    node* newNode = (node*) malloc(sizeof(node));
    newNode->data = *door;
    newNode->next = NULL;
    return newNode;
}

node* add_door(node* elem, door* door) {
    node* newNode = (node*) malloc(sizeof(node));
    newNode->data = *door;
    newNode->next = NULL;

    if (elem == NULL) {
        return newNode;
    }

    node* current = elem;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return elem;
}

node* find_door(int door_id, node* root) {
    node* current = root;
    while (current != NULL) {
        if (current->data.id == door_id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

node* remove_door(node* elem, node* root) {
    if (elem == NULL || root == NULL) {
        return root;
    }

    if (root->data.id == elem->data.id) {
        node* temp = root;
        root = root->next;
        free(temp);
        return root;
    }

    node* current = root;
    while (current->next != NULL && current->next->data.id != elem->data.id) {
        current = current->next;
    }

    if (current->next == NULL) {
        return root;
    }

    node* temp = current->next;
    current->next = current->next->next;
    free(temp);
    return root;
}

void destroy(node* root) {
    node* current = root;
    while (current != NULL) {
        node* temp = current;
        current = current->next;
        free(temp);
    }
}
