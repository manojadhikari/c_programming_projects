//Manoj Adhikari
//Coen 12, Monday 2:15pm
//Count the number of words in a file

#include <stdio.h>
#define MAX_WORD_LENGTH 30
int main (int argc, char *argv[1]){//argv[1] pointer points to the filename
		FILE *fp;
		char *p;
		int counter;
		fp=fopen(argv[1],"r");//open the file received
		if(fp==NULL){//check if the file was 0
				return 0;
		}
		char string[MAX_WORD_LENGTH+1];
		while(fscanf(fp,"%s",string)==1){//as long as there is a word you increase the counter
				counter++;
		}
		printf("%d words \n",counter);//you print the number of words
		return 0;//returns an integer for integer function
}
