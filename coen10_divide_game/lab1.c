# include <stdio.h>
# include <stdlib.h>
# include <time.h>
int divider(int,int,int); //prototyping the function
int main(){
	int counter=0;int x; int i; int d; int p; int q;
	srand((int) time(NULL));//initialize the random number generator by passing the argument seed. 
	for (i=0;i<10;i++){//This loop calls divider function and passes arguments
		d=rand()%12+1;
		q=rand()%13;
		p=d*q;
		x=divider(d, q, p);
		if (x==1){
			printf ("You are correct!\n");
			counter++;//counts the number of correct responses
		}
		else{
			printf ("You are wrong!");
			printf ("The correct answer is %d \n", q);
		}
	}
	printf ("Correct responses: %d \n",counter);//outputs the number of correct responses
}

int divider(int d,int q,int p){//this function receives an input from the user and check it with the quotient value. 
	printf("What is %d / %d ? \n", p, d);
	int a;
	scanf ("%d", &a);
	if (a==q)
		return 1;
	else
		return 0;
}







