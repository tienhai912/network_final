#ifndef HORSEDLL_H_   /* Include guard */
#define HORSEDLL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
  int horseID;
  int playerID;
  int location;
  int stepMoved;
}horse;

typedef struct node1 {
   horse *horse;
  
   struct node1 *next;
   struct node1 *prev;
} node;

typedef struct {
   //this link always point to first Link
   node *head;

   //this link always point to last Link 
   node *last;
} horseList;

horseList* newHorseList();

horse* newHorse(int horseID, int playerID, int location);

int lastID(horseList* hl);

horse* findHorseInList(horseList* hl, int horseID);

int isEmpty(horseList* hl);

int length(horseList* hl);

void displayForward(horseList* hl);

void insertFirst(horseList* hl, horse* newHorse);

void insertLast(horseList* hl, horse* newHorse);

node* deleteFirst(horseList* hl);

node* deleteLast(horseList* hl);

node* delete(horseList* hl, horse* dHorse);

#endif
