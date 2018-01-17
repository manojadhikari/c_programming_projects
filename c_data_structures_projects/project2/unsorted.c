//Manoj Adhikari
//Monday 2:15
//Project #2

//This is an unsorted implementation of abstract data types for string. Several function that interact with three files, unique.c, parity.c, and bincount.c are included in this file. These functions are designed such that the datas are not sorted. 

# include <stdio.h>
# include <assert.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

typedef struct set SET;

int findElement(SET *sp, char *elt);//prototyping a function

struct set{
		int count;
		int length;
		char ** elts;
};

//This function creates a new SET by using malloc for SET and the Char * for elts inside the set  O(1)
SET *createSet (int maxElts){
		SET *sp;
		sp=malloc(sizeof(SET));
		assert (sp!=NULL);
		sp->count=0;
		sp->length=maxElts;
		sp->elts=malloc(sizeof(char*)*maxElts);
		assert(sp->elts!=NULL);
		return sp;
}

//This function frees the set and array * that were created using malloc one by one  O(n)
void destroySet(SET *sp){
		assert (sp!=NULL);
		int i;
		for (i=0;i<sp->count;i++){
			free(sp->elts[i]);
		free(sp);
		return;
	}
}

//This function returns the numbers of elements stored as count in the set.  O(1)
int numElements(SET *sp){
		assert (sp!=NULL);
		return sp->count;
}

//This function checks if the array elts has an element that we are searching using findElement function O(n)
bool hasElement(SET *sp, char *elt){
		assert (sp!=NULL&&elt!=NULL);
		int pos;
		pos=findElement (sp,elt);
		if (pos==-1)
				return false;
		return true;
}

//This function checks to see if there is already a copy of element we are trying to add and creates a new element if there is none and if there is space in the array  O(n)
bool addElement (SET *sp, char *elt){
		assert (sp!=NULL && elt!=NULL);
		int pos;
		pos=findElement(sp,elt);
		if (pos!=-1||sp->count==sp->length)
				return false;
		elt=strdup(elt);
		assert(elt!=NULL);
		sp->elts[sp->count++]=elt;
		return true;
}

//This function searches for a matching element and removes it from the elts array if it is found. O(n)
bool removeElement (SET *sp, char *elt){
		assert (sp!=NULL&&elt!=NULL);
		int pos;
		pos=findElement(sp,elt);
		if(pos==-1){
				return false;
		}
		free(sp->elts[pos]);
		sp->elts[pos]=sp->elts[sp->count-1];
		sp->elts[sp->count-1]=NULL;
		sp->count--;
		return true;
}

//This function helps us to see if we have the match of the element we are searching and returns the position if found. It returns -1 if the function is not found.  O(n)
int findElement (SET *sp, char *elt){
			assert (sp!=NULL&&elt!=NULL);
			int i;
			for (i=0;i<sp->count;i++){
					if(strcmp(sp->elts[i],elt)==0)
							return i;
			}
			return -1;
}
