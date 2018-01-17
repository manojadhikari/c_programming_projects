//Manoj Adhikari
//Monday 2:15
//Project #2, sorted.c

//This file includes functions that create a set and it's elements in sorted order. The functions in this file make sure the list stays sorted while modifying the set. 
# include <stdio.h>
# include <assert.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

typedef struct set SET;

int findElement (SET *sp, char *elt, bool *found);
bool bSearch (int a[], int lo, int hi, int x);

struct set{
		int count;
		int length;
		char ** elts;
};

//This function creates a new SET by using malloc for SET and the char * for elts inside the set.   O(1)
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

//This function frees the set and array * that were created using malloc one by one   O(n)
void destroySet(SET *sp){
		assert (sp!=NULL);//not correct
		int i;
		for (i=0;i<sp->count;i++){
			free(sp->elts[i]);
		free(sp);
		return;
	}
}

//This function ruturns the numbers of elements stored as count in the set   O(1)
int numElements(SET *sp){
		assert (sp!=NULL);
		return sp->count;
}

//This function checks if the array elts has an element that we are searching using findElement function    O(logn)
bool hasElement(SET *sp, char *elt){
		assert (sp!=NULL&&elt!=NULL);
		int pos;
		bool found;
		pos=findElement (sp,elt,&found);
		if (found==false)
				return false;
		return true;
}

//This function checks to see if there is already a copy of element we are trying to add and creates a new element if there is none and if there is space in the array.   O(n)
bool addElement (SET *sp, char *elt){
		assert (sp!=NULL&&elt!=NULL);
		int i;
		int pos;
		bool found;
		pos=findElement(sp,elt,&found);
		if (found==true||sp->count==sp->length)
				return false;
		elt=strdup(elt);
		assert(elt!=NULL);
		for (i=sp->count;i>pos;i--)
				sp->elts[i]=sp->elts[i-1];
		sp->elts[pos]=elt;
		sp->count++;
		return true;
}

//This function searches for a matching element and removes it from the elts array if it is found.   O(n)
bool removeElement (SET *sp, char *elt){
		assert (sp!=NULL&&elt!=NULL);
		int pos;
		int i;
		bool found;
		pos=findElement(sp,elt,&found);
		if(found==false){
				return false;
		}
		for(i=pos;i<sp->count;i++)
				sp->elts[i]=sp->elts[i+1];
		sp->count--;
		return true;
}

//This function checks to see if there is a match of the element we are searching for and returns the position of lowest number because that is where the number we are searching for belongs. This function uses binary search.   O(logn)
int findElement (SET *sp, char *elt, bool *found){
		assert (sp!=NULL&&elt!=NULL&&found!=NULL);
		int lo; int hi; int mid; int diff;
		lo=0;
		hi=sp->count-1;
		while (lo<=hi){
				mid=(lo+hi)/2;
				diff=strcmp(elt,sp->elts[mid]);
				if (diff<0)
						hi=mid-1;
				else if (diff>0)
						lo=mid+1;
				else{
						*found=true;
						return mid;
				}
		}
		*found=false;
		return lo;
}
