//Manoj Adhikari
//Wed 5:15, Silvia Figueira
//Restaurant Waitlist

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int counter=0;
int number[10];
char guests[20][20]; 
void insert();
void replace(); 
void list();
int  main(){
	int a;
	while(1){
	printf ("Please enter the followning: \n 1: To insert new name\n 2: To remove a name \n 3: To view the list\n");
	scanf("%d",&a);//Stores the value entered by the user in the address of a
		switch (a){//goes to different functions depending on the values entered by user
			case 1:
				insert();
				break;
			case 2:
				replace();
				break;
			case 3: 
				list();
				break;
			case 4:
				return 0;//returns if user enters 4
		}
	}
	return 0;
}
void insert(){//This function is used for inserting name and numbers to our arrays
	if (counter==10){//if the list is full, no reservations can be made
		printf("Sorry. There is no more place. \n");
		return;
	}
	int i=0; 
	char b[10];
	int a; 
	printf ("Please enter guest name  \n");
	scanf("%s",b);//The name entered by the user is stored in the array b
	for (i=0; i<counter; i++){//Checks to see if the person had made an appointment before
		if (strcmp(b,guests[i])==0){
			printf("This person already has an appointment \n");
				break;//breaks if it finds the matching name on the list
		}
	}
	if(i==counter){//if no matches were found, reservation can be made
		printf("No of people?? \n");
		scanf("%d",&a);
		number[counter]=a;//number of people goes to the end of number array
		strcpy(guests[counter],b);//the name of customer is copied to the end of guests array
		counter++;
	}
	return;
}

void list(){//This function displays the list to the user
	if (counter==0){//if there were no reservations made, it returns
		printf("The list is empty \n");
		return;
	}
	int i;
	printf("The list is as follows: \n");
	for (i=0; i<counter; i++){//If there were reservations, then the list is displayed from oldest to newest
		printf("%d : %s, %d people \n",i+1,guests[i],number[i]);//no in the list, customer name, and numbers of people are shown
	}
	return;
}

void replace(){//This function helps us assign tables for customers
	if(counter==0){//if the list is empty, it returns
		printf("No customer yet \n");
		return;
	}
	int i=0;
	int nearest=0;
	int pos=0;
	int d;
	int c;
	int j;
	printf("What is the table size that is available? \n");
	scanf("%d",&c);//stores the size of table on c
	while(number[i]>c){//Compares the numbers from number array and increments if people won't fit in the table
		i++;
		if(i==counter){//if all numbers are bigger than table size, the function returns
			printf("The table is too small! \n");
			return;
		}
	}


	nearest=(c-number[i]);//the variable nearest stores the difference between the table size and the first small group in the number array
	pos=i;//pos variable stores where the first small group was on the array
	for(;i<counter;i++){//This loops helps to see if there are other groups that fit better with the table available
		if (number[i]<=c){//when smaller number is found this statement executes
			d=(c-number[i]);//the difference between the table and no of people is stored in d
			if(d<nearest){//this statement checks if the difference was smaller than the previous difference
				nearest=d;//if it was, this difference is replaces the older one
				pos=i;//the position of the element in number array is stored
			}
		}
	}
	printf("The next table is for %s \n",guests[pos]);
	counter--;//counter is decremented when the table is assigned

	for(i=pos;i<(counter-1);i++){//all  customers after the group that got table are shifted up
		strcpy(guests[i],guests[i+1]);//shifted up in guests array
		number[i]=number[i+1];//shifted up in number array
		guests[i+1][0]='\0';
	}
	
	return;
}

