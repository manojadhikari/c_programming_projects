/*
    Manoj Adhikari
	Monday 2:15
	Project #3, Hashing

	This file includes a sorting algorithm to demonstrate the versatility of a deque. 
	This program reads in a sequence of non-negative integers from the standard input and then writes them back in sorted order on the standard output. 
	Radix sorting uses queues as its main data structures. 
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"
#include <math.h>

int main(){
		int test;//Declaring the decessary variables
		int a;
		int pos;
		int i;
		int j;
		int c;
		int length;
		int item;
		int count_Deque;
		int max=0;	
		DEQUE *dp;
		DEQUE *array[10];
		DEQUE *list=createDeque();

		/*
		   This loop fills in every indexes of the array with a deque pointer		   
		 */
		for(i=0;i<10;i++)
				array[i]=createDeque();

		printf("Enter values \n");

		/*
			This loop receives numbers from the user and put them in a deque pointed by list *
		 */
		while(1){
				
				if(scanf("%d",&a)!=1){//break out of the loop if a positive number is not entered
						break;
				}
				//keeping track of the maximum value entered
				if(a>max)
						max=a;

				addLast (list, a);//add the new node to the deque
		}

		length=(log(max+1)/log(10));//This calculates the length of the the maximum value

		/*
   			The outer for loop helps us to run the sorting process based on the length of the maximum value.
   			*/
		for(i=0;i<=length;i++){
				count_Deque=numItems(list);//we call numItems to find out how many times we have to loop the deque

				/*
				   This loop copies the data from the list deque into the array
				   We use removeFirst and addLast functions becuase it is a queue and follows FIFO property
				 	*/

				for (c=0;c<count_Deque;c++){
						item=removeFirst(list);

						test=item/(pow(10,i));//divide the item by power of 10 to test a specific digit using modulo
						pos=test%10;
						addLast(array[pos],item);
				}

				/*
				   This loop traverses the array and each deques to put the data back into the list deque
				  */
				for (j=0;j<10;j++){
						dp=array[j];
						count_Deque=numItems(dp);
						
						/*
						   This loop traverses the deque if it has one or more node with data
						   */
						for (c=0;c<count_Deque;c++){
								item=removeFirst(dp);
								addLast(list,item);//Adds the data to the list deque
						}
						

				}
		}
		
		count_Deque=numItems(list);
		/*
		   After the sorting process has been completed, This loop removes the items from the deque and prints the data
		   */
		for(i=0;i<count_Deque;i++){
				item=removeFirst(list);
				printf ("%d \t",item);
		}
		printf("\n");
		/*
		   Destroying the deque that we just created
		   */
		for (j=0;j<10;j++){
				dp=array[j];
				destroyDeque(dp);
		}

		destroyDeque(list);

}
