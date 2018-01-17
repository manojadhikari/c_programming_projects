/*
    Manoj Adhikari
	Monday 2:15
	Project #3, Hashing

	This file includes functions that create a set and store it's elements in a hash table in order to make our program more time efficient. 
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"

#define EMPTY 'E'
#define DELETED 'D'
#define FILLED 'F'

/*
typedef struct set SET;
 */
int findElement(SET *sp, char *elt, bool *found);

struct set{
		int count;
		int length;
		char **elts;
		char *flags;
};


/*
   This function creates a new SET by using malloc and the char * for elts and flags inside the set. 
   General Case: O(n), Worst Case: O(n)
 */
SET *createSet (int maxElts){
		SET *sp;
		sp=malloc (sizeof(SET));
		assert (sp!=NULL);
		sp->count=0;
		sp->length=maxElts;
		sp->elts=malloc (sizeof(char*)*maxElts);//This creates an array which stores character pointers
		assert(sp->elts!=NULL);
		sp->flags=malloc (sizeof(char)*maxElts);//This creates an array which stores characters
		assert(sp->flags!=NULL);
		int i;

		for(i=0;i<maxElts;i++)//This loop initializes all the values inside flags array as empty
				sp->flags[i]=EMPTY;

		return sp;
}

/*
	This function generates the hash key. It was provided in the lab assignment.
	 Best Case: O(1), Worst Case: O(n)
 */
unsigned hashString(char *s){
		unsigned hash=0;

		while (*s != '\0')
				hash = 31 * hash + *s ++;

		return hash; 
}
	
/*
	This function frees the set and array * that were created using malloc one by one.
	General case: O(n), Worst Case: O(n)
 */
void destroySet (SET *sp){
		assert (sp!=NULL);
		int i;

		for (i=0;i<sp->count;i++)//Frees the individual pointers in the elts array inside the set
				free (sp->elts[i]);

		free (sp->elts);
		free (sp->flags);
		free (sp);

		return;
}

/*
	This function returns the numbers of elements stored as count in the set
	Best Case: O(1), Worst Case: O(1)  
 */
int numElements (SET *sp){
		assert (sp!=NULL);
		return sp->count;
}

/*
	This function checks if the array elts has an element that we are searching using findElement function 
	General Case: O(n), Worst Case: O(n)  
 */
bool hasElement (SET *sp, char *elt){
		assert (sp!=NULL&&elt!=NULL);
		int pos;
		bool found;//We declate a variable that we can pass to findElement function
		pos=findElement(sp,elt,&found);

		if (found==false)
				return false;

		return true;
}

/*
	This function helps us to add an element in our table after finding the best spot. 
	General Case: O(n), Worst Case: O(n)  
 */
bool addElement (SET *sp, char *elt){
		assert (sp!=NULL&&elt!=NULL);
		int pos;
		int i;
		bool found;
		pos=findElement(sp,elt,&found);

		if (found==true||sp->count==sp->length)//if the element already exists we can not add it.
				return false;

		elt=strdup(elt);
		assert(elt!=NULL);
		sp->elts[pos]=elt;
		sp->flags[pos]=FILLED;//changing flag as filled after we add an element
		sp->count++;

		return true;
}

/*
	This function searches for and removes the element pointed by char *elt. It calls findElement to see if the element exists in the table. 
	General Case: O(n), Worst Case: O(n)  
 */
bool removeElement (SET *sp, char *elt){
		assert (sp!=NULL&&elt!=NULL);
		int pos;
		int i;
		bool found;
		pos=findElement(sp,elt,&found);

		if (found==false||sp->count==0)
				return false;
		
		sp->flags[pos]=DELETED;//The flag becomes deleted after removing an element
		sp->count--;

		return true;
}

/*
	This is a findElement function and it returns the position of an element in the hash table.
	Best Case: O(1), Worst Case: O(n)  
 */
int findElement(SET *sp, char *elt, bool *found){
		assert(sp!=NULL && elt!=NULL && found!=NULL);
		unsigned pos;
		int i=0;
		pos=hashString(elt);
		int first_slot=-1;//first slot will store the first available space

		while (sp->flags[(pos+i)%sp->length]!=EMPTY){//loop until you reach an empty slot.

				if(i==sp->length)//break if you traversed the loop for more than maxElts
						break;

				if (first_slot==-1 && sp->flags[(pos+i)%sp->length]==DELETED)
						first_slot=(pos+i)%sp->length;//Remember the slot where you saw the first deleted
			
				if (sp->flags[(pos+i)%sp->length]==FILLED && strcmp(sp->elts[(pos+i)%sp->length],elt)==0){
						*found=true;
						return ((pos+i)%sp->length);//return the position if found
				}

				i++;
		}

		if (first_slot==-1)
				first_slot=(pos+i)%sp->length;

		*found=false;
		return first_slot;//return first_slot if not found
} 
