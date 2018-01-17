/*
    Manoj Adhikari
	Monday 2:15
	Project #5, Tree

	This file includes functions that create a tree and perform operations related to adding, removing, and searching data in the tree. 
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include <ctype.h>
#include "pack.h"
		
struct tree* leaves[257];
struct tree* heaps[257];
int counts [257];
int n=0;//Variable that will be used for counting the number of trees

void insert (struct tree* t);
struct tree* delete (void);
void print (struct tree* t);

int main(int argc, char* argv[]){
		
		FILE *fp;
		fp=fopen(argv[1],"r");
		assert (fp!=NULL);
		
		int i;
		for (i=0;i<257;i++){//initializing the count of all the characters to be 0 at the start
				counts[i]=0;
		}

		int c;
		while ((c=fgetc(fp))!=EOF){//Counting the characters from the file and increasing their counter
				counts[c]++;
		}
		//Creating a binary tree consisting of just a leaf for each character with a nonzero count. 
		
		for (i=0;i<256;i++){
		
				if (counts[i]!=0){//Traversing the counts array to see which characters were in the file
						leaves[i]= createTree (counts[i],NULL,NULL);//Creating a root * and storing it in the pq array
						insert(leaves[i]);//This function inserts the tree from the leaves into the heaps
						n++;
				}
		}

		leaves[i]=createTree (0,NULL,NULL);//creating a tree with a zero count for the end of file marker. 
		heaps [n]=leaves[i];

//Removing the two lowest priority trees. Creating a new tree with each of these trees as subtrees
		int min;
		int min1;
		int pos;
		int pos1;
		int sum;

		while (n>3){//because you won't have the value to compare if you have less than 3 trees in your heap. 
				pos=0;
				min=getData (heaps[0]);//This is a min-heap

				if (getData (heaps[1])<getData (heaps[2])){//Find if the 2nd minimum value is in pos 1 or 2
						min1=getData (heaps[1]);
						pos1=1;
				}

				else{
						min1=getData (heaps[2]);
						pos1=2;
				}
				
				sum=min+min1;
				struct tree* new = createTree (sum, heaps[pos], heaps[pos1]);//Create a new heap that contains the data which is the sume of 2 mins.	
				heaps[pos1]=heaps[n];//Replace the tree with 2nd min value with the last value in the array
				n--;
//After you replace the 2nd value with the last, swap it to put it in the right place 
				
				while (pos1<=n){//Looping until you find the best spot for the data in the pos1, pos1 can't be greater than n
						struct tree* temp;
						temp=heaps[pos1];

						if (2*pos1+1>n)
								break;

						if (2*pos1+1==n){//this means there is no right child
								
								if(getData(heaps[2*pos1+1])<getData(heaps[pos1])){//We only compare with the left child and then break
										heaps[pos1]=heaps[2*pos1+1];//if true we swap
										heaps[2*pos1+1]=temp;
								}

								break;//break after you compared with the only left child you had
						}

						if((sum>getData(heaps[2*pos1+1])||sum>getData(heaps[2*pos1+2]))&&(getData(heaps[2*pos1+1])<getData(heaps[2*pos1+2]))){//Compare to see if you should switch with the right child or the left child. You only do this if there is at least one child that is smaller 
								heaps[pos1]=heaps[2*pos1+1];
								heaps[2*pos1+1]=temp;
								pos1=2*pos1+1;
						}

						else{
								heaps[pos1]=heaps[2*pos1+2];
								heaps[2*pos1+2]=temp;
								pos1=2*pos1+2;
						}

				}

				//Swapping the data on the first index
				heaps[pos]=heaps[n];
				n--;
				while (pos<=n){//Looping until you find the best spot for the data in the pos1
						
						struct tree* temp;
						temp=heaps[pos];

						if(2*pos+1>n)
								break;

						if (2*pos+1==n){//this means there is no right child
								
								if(getData(heaps[2*pos+1])<getData(heaps[pos])){//We only compare with the left child and then break
										heaps[pos]=heaps[2*pos+1];
										heaps[2*pos+1]=temp;
								}

								break;
						}

						if((sum>getData(heaps[2*pos+1])||sum>getData(heaps[2*pos+2]))&&getData(heaps[2*pos+1])<getData(heaps[2*pos+2])){//Compare to see if you should switch with the right child or the left child.
								heaps[pos]=heaps[2*pos+1];
								heaps[2*pos+1]=temp;
								pos=2*pos+1;

						}

						else{
								heaps[pos]=heaps[2*pos+2];
								heaps[2*pos+2]=temp;
								pos=2*pos+2;
						}
				}
//The code above helps remove two min trees and keep the heaps in min-order

				insert (new);//Insert the new tree that has the sum of two min in the appropriate place
				n++;
		}
		//Segmentation fault after the insert above

		//Now we have only two trees left in our array. So we add them up to make a new only one tree
		pos=0;
		min=getData (heaps[0]);
		if (getData (heaps[1])<getData (heaps[2])){//Again, we find wheather the value is on index 1 or 2
				min1=getData (heaps[1]);
				pos1=1;
		}

		else{
				min1=getData (heaps[2]);
				pos1=2;
		}
		
		sum=min+min1;
		struct tree* new = createTree (sum, heaps[pos], heaps[pos1]);	
		
		heaps[0]=new;//The new tree will be stored in heaps[0]. This is the only tree in our array
		n--;

		for (i=0;i<257;i++){//This loop prints the huffman code for each leaves
				if(counts[i]!=0){
						print(leaves[i]);
				}
		}
		pack (argv[1],argv[2],leaves);
}

void insert (struct tree* t){
		
		int a=n;//new variable set equal to j and will be used for comparing the data with the data in the parent pointe
		heaps[a]=t;

		while (a>0){//we stop when we reach the beginning of the array
			//problem lies here	
				int j=getData(heaps[(a-1)/2]);
				int j1=getData(heaps[a]);

				if (j>j1){//comparing with the data in the parent to see if it is larger and swapping if necessary.
						heaps[a]=createTree(j,NULL,NULL);
						heaps[(a-1)/2]=createTree(j1,NULL,NULL);
				}
				
				a=(a-1)/2;//moving to the previous parent
		}
		return;
}

//This function prints the character (if it is printable). Otherwise it prints its octal value along with the number of occurences and the bit encoding assigned by starting at the root and walking down the tree. 
void print (struct tree* t){
		if (getParent(t)==NULL){//We stop when we reach the root

				if (isprint(getData(t)))//This function returns a non-negative number if the character is printable
						printf("'%c':\t",getData(t));
				
				else {//if the charater is not printable, we print it's octal value
						printf("'");
						int c=getData(t);
						while (c!=0){
								printf("%d",c%8);
								c=c/8;
						}
						printf("':\t");
				}
				
				printf("%d",getData(t));
		}
		if (getLeft(getParent(t))==t){//We compare to see wheather the tree is it's parent's left child or right child. 
				print(getParent(t));
				printf("%d",0);
		}

		else{
				print(getParent(t));
				printf("%d",1);
		}
}


void pack (char *infile, char *outfile, struct tree *leaves[257]);

