/*
 * linkedList.h
 *
 *  Created on: Mar 8, 2024
 *      Author: glmun
 */

#ifndef INC_LINKEDLIST_H_
#define INC_LINKEDLIST_H_

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

Node* createNode(int data);
void insertAtEnd(Node** head, int data);
void connectEndToFirst(Node** head);
#endif /* INC_LINKEDLIST_H_ */
