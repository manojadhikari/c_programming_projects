/*
    Manoj Adhikari
	Monday 2:15
	Project #4, Maze

	This file includes functions that create a deque and perform operations related to adding, removing, and searching data in the deque. 
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"

struct node{
		struct node *next;
		struct node *prev;
		int data;
};

struct deque{
		int count;
		struct node *dummy;
};


/*
   This function creates a new DEQUE by using malloc and sets the counter to 0.  
 O(1)
 */
DEQUE *createDeque (){
		DEQUE *dp;
		dp=malloc (sizeof(DEQUE));
		assert (dp!=NULL);
		dp->dummy=malloc (sizeof(struct node));
		assert (dp->dummy!=NULL);
		dp->dummy->prev=dp->dummy;
		dp->dummy->next=dp->dummy;
		dp->count=0;//seting the deque counter to 0 at the beginning. 
		return dp;
}

/*
	This function frees the set and array * that were created using malloc one by one.
 O(1)
 */
void destroyDeque (DEQUE *dp){
		assert (dp->dummy->next!=NULL);
		struct node *temp;
		temp=dp->dummy->next;

		while (temp!=dp->dummy){//looping the deque to free each nodes
				temp=temp->next;
				free(temp->prev);
		}
		
		free(dp->dummy);
		free(dp);
}
		
/*
	This function returns the number of elements stored as count in the set
 O(1)
 */
int numItems (DEQUE *dp){
		return dp->count;
}

/*
   This function creates a new node with value x and adds it after the dummy node
 O(1)
 */
void addFirst (DEQUE *dp, int x){
	struct node *new;
	new=malloc(sizeof(struct node));
	new->data=x;
	new->next=dp->dummy->next;
	new->prev=dp->dummy;
	dp->dummy->next->prev=new;
	dp->dummy->next=new;
	dp->count++;//increase the deque count after adding a node.
	return;
}

/*
	This function creates a new node with value equal to x and adds it at the end of the Deque. i.e. Before the dummy node 
 O(1)
 */
void addLast (DEQUE *dp, int x){
	struct node *new;
	new=malloc(sizeof(struct node));
	new->data=x;
	new->next=dp->dummy;
	new->prev=dp->dummy->prev;
	dp->dummy->prev->next=new;
	dp->dummy->prev=new;
	dp->count++;
	return;
}

/*
   This function removes and returns the first item in the deque pointed to by dp, the deque must not be empty.
 O(1)
 */
int removeFirst(DEQUE *dp){
		int i;
		assert(dp->dummy->next!=NULL);
		struct node *temp;
		temp=dp->dummy->next;
		dp->dummy->next->next->prev=dp->dummy;
		dp->dummy->next=dp->dummy->next->next;
		
		i=temp->data;//saving the data to return after freeing the node
		free (temp);
		dp->count--;
		return i;
}

/*
   This function removes and returns the last item in the deque pointed to by dp, the deque must not be empty
 O(1)
 */
int removeLast(DEQUE *dp){
		int i;
		assert(dp->dummy->prev!=NULL);
		struct node *temp;
		temp=dp->dummy->prev;
		dp->dummy->prev->prev->next=dp->dummy;
		dp->dummy->prev=dp->dummy->prev->prev;
		
		i=temp->data;//saving the data to return after freeing the node.
		free (temp);
		dp->count--;
		return i;
}

/*
   This function returns the data stored in the first node without removing it
 O(1)
 */
int getFirst(DEQUE *dp){
		assert(dp->dummy->next!=NULL);
		int i;
		i=dp->dummy->next->data;
		return i;
}

/*
   This function returns the data stored in the last node without removing it
 O(1)
 */
int getLast(DEQUE *dp){
		assert(dp->dummy->prev!=NULL);
		int i;
		i=dp->dummy->prev->data;
		return i;
}
