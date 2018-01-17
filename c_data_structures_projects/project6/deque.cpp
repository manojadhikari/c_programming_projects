/*
    Manoj Adhikari
	Monday 2:15
	Project #6, C++ Deque interface

	This file includes functions that create a deque and perform operations related to adding, removing, and searching data in the deque. 
 */

#include <cassert>
#include "deque.h"

 /*
   This function is a constructor and initializes the pointers and counter in the deque.  
 O(1)
 */
Deque :: Deque (){
		dummy= new node;
		dummy->prev=dummy;
		dummy->next=dummy;
		
		count=0;//seting the deque counter to 0 at the beginning. 

}

/*
 This function is a destructor and it helps us delete all the nodes in the deque
   O(1)
 */
Deque :: ~Deque(){
		struct node* np, *next;
		np=dummy;

		do {
				next=np->next;
				delete [] np;
				np=next;
		} while (np != dummy);

}
		
/*
	This function returns the number of elements stored as count in the set
 O(1)
 */
int Deque :: size(){
		return count;
}

/*
   This function creates a new node with value x and adds it after the dummy node
 O(1)
 */
void Deque :: addFirst (int x){
	node *fresh;
	fresh=new node;
	fresh->data=x;

	count++;//increase the deque count after adding a node
	
	fresh->next=dummy->next;
	fresh->prev=dummy;

	dummy->next->prev=fresh;
	dummy->next=fresh;
	
	return;
}

/*
	This function creates a new node with value equal to x and adds it at the end of the Deque. i.e. Before the dummy node 
 O(1)
 */
void Deque :: addLast (int x){
	node *fresh;
	fresh=new node;
	fresh->data=x;

	fresh->next=dummy;
	fresh->prev=dummy->prev;
	
	dummy->prev->next=fresh;
	dummy->prev=fresh;
	count++;

	return;
}

/*
   This function removes and returns the first item in the deque pointed to by dp, the deque must not be empty.
 O(1)
 */
int Deque::removeFirst(){
		assert(dummy->next!=NULL && count >0);

		int i;
		node *temp;

		temp=dummy->next;
		i=temp->data; //saving the data to return after freeing the node

		dummy->next->next->prev=dummy;
		dummy->next=dummy->next->next;
		
		delete [] temp;
		count--;

		return i;
}

/*
   This function removes and returns the last item in the deque pointed to by dp, the deque must not be empty
 O(1)
 */
int Deque::removeLast(){
		assert(dummy->prev!=NULL);

		int i;
		node *temp;

		temp=dummy->prev;
		i=temp->data;//data to return after deleting the node.

		dummy->prev->prev->next=dummy;
		dummy->prev=dummy->prev->prev;
		
		delete []temp;
		count--;

		return i;
}

/*
   This function returns the data stored in the first node without removing it
 O(1)
 */
int Deque::getFirst(){
		assert(dummy->next!=NULL);
		int i;
		i=dummy->next->data;
	
		return i;
}

/*
   This function returns the data stored in the last node without removing it
 O(1)
 */
int Deque::getLast(){
		assert(dummy->prev!=NULL);
		int i;
		i=dummy->prev->data;
		
		return i;
}
