//Manoj Adhikari
//Wed 5:15, Silvia Figueira
//Restaurant Waitlist using structs

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define WAITLIST struct waitList
struct waitList{//defining a struct with two types of member variables
	int number;
	char guests[20];
};
struct waitList Array[20];//defining struct array that will have 20 structs
int counter=0;
void insert();
void replace(); 
void list();
void fitList();//prototyping the functions
int  main(){
	int a;
	while(1){
	printf ("Please enter the followning: \n 1: To insert new name\n 2: To remove a name \n 3: To view the list\n 4: To view the fitList \n");
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
				fitList();
				break;
			case 5:
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
	struct waitList *p = Array;
	printf ("Please enter guest name  \n");
	scanf("%s",b);//The name entered by the user is stored in the array b
	for (i=0; i<counter; i++,p++){//Checks to see if the person had made an appointment before
		if (strcmp(b,p->guests)==0){
			printf("This person already has an appointment \n");
				break;//breaks if it finds the matching name on the list
		}
	}
	if(i==counter){//if no matches were found, reservation can be made
		printf("No of people?? \n");
		scanf("%d",&a);
		p->number=a;//number of people goes to the end of number array
		strcpy(p->guests,b);//the name of customer is copied to the end of guests array
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
	struct waitList *p=Array;
	printf("The list is as follows: \n");
	for (i=0; i<counter; i++,p++){//If there were reservations, then the list is displayed from oldest to newest
		printf("%d : %s, %d people \n",i+1,p->guests,p->number);//no in the list, customer name, and numbers of people are shown
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
	int d;
	int c;
	int j;
	struct waitList *p=Array;//seting the pointer p to the initial of array
	printf("What is the table size that is available? \n");
	scanf("%d",&c);//stores the size of table on c
	while((p->number)>c){//Compares the numbers from number inside struct array  and increments if people won't fit in the table
		i++;
		p++;
		if(i==counter){//if all numbers are bigger than table size, the function returns
			printf("The table is too small! \n");
			return;
		}
	}


	nearest=(c-(p->number));//the variable nearest stores the difference between the table size and the first small group in the number array
	struct waitList *q=p;//pointer q points to the same address as p
	int pos=i;//pos variable stores where the first small group was on the array
	for(;i<counter;i++,p++){//This loops helps to see if there are other groups that fit better with the table available
		if (p->number<=c){//when smaller number is found this statement executes
			d=(c-p->number);//the difference between the table and no of people is stored in d
			if(d<nearest){//this statement checks if the difference was smaller than the previous difference
				nearest=d;//if it was, this difference is replaces the older one
				q=p;//the address of the most fit is stored
				pos=i;//the position of the most fit is stores in pos
			}
		}
	}
	printf("The next table is for %s \n",q->guests);
	counter--;//counter is decremented when the table is assigned

	for(i=pos;i<(counter-1);i++,p++){//all  customers after the group that got table are shifted up
		strcpy(p->guests,(p+1)->guests);//shifted up in guests array
		p->number=(p+1)->number;//shifted up in number array
	}
	(p+1)->guests[0]='\0';
	
	return;
}

void fitList(){//Checks to see if there is a group of people that fits to a table available
	if(counter==0){
		printf("There is no customer \n");
		return;
	}
	struct waitList *p=Array;//Seting pointer p to the beginning of array
	int c;
	int i;
	int j;
	int flag;
	printf("Please enter the table size \n");
	scanf("%d",&c);//stores table size on c
	printf("Fit list: \n");
	for(i=0;i<counter;i++,p++){
		if(p->number==c)//compares number inside each structs in array
			printf("%s fits on this table \n",p->guests);
			flag=1;
	}
	if(flag!=1)//prints no fit found if there is no fit
		printf("No Fit found \n");
	return;
}

