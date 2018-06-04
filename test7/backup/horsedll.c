#include "horsedll.h"

//make new horse list
horseList* newHorseList(){
  horseList* temp = (horseList*) malloc(sizeof(horseList*));
  temp->head = NULL;
  temp->last = NULL;

  return temp;
}

//make new horse
horse* newHorse(int horseID, int playerID, int location){
  horse* tempHorse = (horse*) malloc(sizeof(horse*));
  tempHorse->horseID = horseID;
  tempHorse->playerID = playerID;
  tempHorse->location = location;
  tempHorse->stepMoved = 0;

  return tempHorse;
}

//last horse ID
int lastID(horseList* hl) {
   if (hl->last == NULL)
      return 0;
   else return hl->last->horse->horseID;
}

//find horse in list
horse* findHorseInList(horseList* hl, int horseID){
   node *current;

   for(current = hl->head; current != NULL; current = current->next){
      if (current->horse->horseID == horseID) return current->horse;
   }

   return NULL;
}

//is list empty
int isEmpty(horseList* hl) {
   return hl->head == NULL;
}

int length(horseList* hl) {
   int length = 0;
   node *current;

   for(current = hl->head; current != NULL; current = current->next){
      length++;
   }

   return length;
}

//display the list in from first to last
void displayForward(horseList* hl) {

   //start from the beginning
   node *ptr = hl->head;

   //navigate till the end of the list
   printf("\n[ ");

   while(ptr != NULL) {
      printf("(%d, %d, %d) ",ptr->horse->horseID, ptr->horse->playerID, ptr->horse->location);
      ptr = ptr->next;
   }

   printf(" ]\n");
}


//insert link at the first location
void insertFirst(horseList* hl, horse* newHorse) {

   //create a link
   node *link = (node*) malloc(sizeof(node));
   link->horse = newHorse;

   if(isEmpty(hl) == 1) {
      //make it the last link
      hl->last = link;
   } else {
      //update first prev link
      hl->head->prev = link;
   }

   //point it to old first link
   link->next = hl->head;

   //point first to new first link
   hl->head = link;
}

//insert link at the last location
void insertLast(horseList* hl, horse* newHorse) {

   //create a link
   node *link = (node*) malloc(sizeof(node));
   link->horse = newHorse;

   if(isEmpty(hl) == 1) {
      //make it the last link
      hl->head = link;
   } else {
      //make link a new last link
      hl->last->next = link;
      //mark old last node as prev of new link
      link->prev = hl->last;
   }

   //point last to new last node
   hl->last = link;
}

//delete first item
node* deleteFirst(horseList* hl) {

   //save reference to first link
   node *tempLink = hl->head;

   //if only one link
   if(hl->head->next == NULL){
      hl->last = NULL;
   } else {
      hl->head->next->prev = NULL;
   }

   hl->head = hl->head->next;
   //return the deleted link
   return tempLink;

   //NOTE: free deleted link
   //free(tempLink);
}

//delete link at the last location

node* deleteLast(horseList* hl) {

   //save reference to last link
   node *tempLink = hl->last;

   //if only one link
   if(hl->head->next == NULL) {
      hl->head = NULL;
   } else {
      hl->last->prev->next = NULL;
   }

   hl->last = hl->last->prev;

   //return the deleted link
   return tempLink;
}

//delete a link with given key

node* delete(horseList* hl, horse* dHorse) {

   //start from the first link
   node* current = hl->head;
   // node* previous = NULL;

   //if list is empty
   if(hl->head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->horse != dHorse) {
      //if it is last node

      if(current->next == NULL) {
         return NULL;
      } else {
         //store reference to current link
         // previous = current;

         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == hl->head) {
      //change first to point to next link
      hl->head = hl->head->next;
   } else {
      //bypass the current link
      current->prev->next = current->next;
   }

   if(current == hl->last) {
      //change last to point to prev link
      hl->last = current->prev;
   } else {
      current->next->prev = current->prev;
   }

   return current;
}
