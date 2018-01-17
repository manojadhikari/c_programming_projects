//Manoj Adhikari
//Wednesday 5:15
//lab8.c
/*
 This is lab project where we keep track of hotel system and find the users that are best suitable for an empty table in a restaurant using pointers and dynamic memory allocation.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NODE struct node//defining a variable NODE that has the info of struct node
struct node{//defining the variables inside node                                
		        char gName[10];
		        int number;
				NODE *next;
};

void insert(NODE *p, char *name, int a,int pos);//prototyping functions
void assign(NODE *, int, int);
void check(char *,int,int);
void list();
void read_file(char argv[1]);
void save_file(char argv[1]);
int read_ch(char *);
void quit_rec(NODE *p);
void read_backwards();
void rec_func(char *);
void save_rec(int, NODE*,FILE *);
void * auto_save(void *filename);
void read_binFile(char *);
NODE *heads[4];
NODE *tails[4];
pthread_mutex_t mutex;//declaring mutex

int main(int argc, char*argv[]){//Receiving arguments while running the program about the pointer to the filename and the number of arguments passed
		char name[10];
		int number;
		int x;
		int flag=0;
		int size;
		char empty;
		char ch;

		pthread_t thread;//declaring a thread
		pthread_mutex_init (&mutex, NULL);//We need to initialize the mutex so that we can use it for locking and unlocking
		pthread_create(&thread,NULL,auto_save,(void *)argv[2]);
		if (argc==1){//The name of the file is on 2nd argument so if argc is 1, we return
				printf("The name of the file is missing! \n");
				return 1;
		}
		read_file(argv[1]);//Pass the filename to a function that will convert text files to linked lists. 
		while(1){//forever loop
			printf("Please enter: \n 1: To insert \n 2: To assign \n 3: To list \n 4: To read a character \n 5: To read names backwards\n  6: To read from the binary file \n7: To quit \n");
			scanf("%d",&x);
			switch(x){//switches based on the user's preference
					case 1:
							printf("Please enter your name \n");
							scanf("%s",name);
							int i;
							flag=0;
							for (i = 0; i < 4; i++){
								NODE*p=heads[i];
								while(p!=NULL){//Loop for checking the repetition of names
										printf("%s \n",p->gName);
										if(strcmp(p->gName,name)==0){
												printf("This name already exists \n");
												flag=1;
												break;
										}
									p=p->next;
								}
							}
							if (flag!=1){//if the name is not repeated, inserting begins
							printf("Please enter group size \n");
							scanf("%d",&number);
							check(name,number,1);
							}
							break;
					case 2:
							printf("Please enter the table size \n");
							scanf("%d",&size);
							printf("Test before check \n");
							check(&empty,size,2);//just having random value for the string it will not make a difference on the code
							break;
					case 3:
							list();
							break;
					case 4:
							printf("Enter character to count \n");
							scanf("%s",&ch);
							read_ch(&ch);
							break;
					case 5:
							read_backwards();
							break;
					case 6:
							read_binFile(argv[2]);//Passing the second filename to the function that reads from our binary file
							break;
					case 7:
							save_file(argv[1]);//new function to save the list into a binary file automatically
							return 0;
			}
		}
}

void read_file(char* filename){//read files from text-file
		FILE *fp;//declaring a new file pointer
		char name[10];
		int number;
		fp=fopen(filename,"r");//passing the address of file and the action to perform in it
		if(fp==NULL)//if the file is empty, return
				return;
		fseek(fp,40,SEEK_SET);//fseek helps us to skip reading 40 places in fp, starting at the beginning(SEEK_SET).
		while((fscanf(fp,"%s%d",name,&number)==2)){//reads a string and number from fp into the address of name and number
				check(name,number,1);//calling insert function, the arguments are the name and number received from fp.
		}

		fclose(fp);//closes the file
		return;
}


void save_file(char* argv){//receives the pointer to the file where info is to be saved
		FILE *fp;//declare local pointer
		fp=fopen(argv,"w");//passing the address of the file to write on
		if(fp==NULL)//if the pointer is null there is no file, so you can't save
				return;
		fprintf(fp,"Group name\t, Number \n------------------\n");//setting header for the list
		printf("arrived 1 \n");
		int i=0;
		for(i=0;i<4;i++){
			NODE *p=heads[i];
			while(p!=NULL){//copies list from linked list to text file
				fprintf(fp,"%s\t%d",p->gName,p->number);
				p=p->next;
			}
			quit_rec(heads[i]);
		}
		fclose(fp);//closes the file
		return;
}
void quit_rec(NODE *p){
		if(p==NULL)
				return;
		quit_rec(p->next);
		free(p);
		return;
}
void check(char *name, int size,int task){//Comments are included in the lab8 version
		int pos=0;
		int i;
		printf("insert got here \n");
		for(i=1;i<7;i+=2){
			if(i<=size&&size<i+2){
				switch (task){
					case 1:
							insert(heads[pos],name,size,pos);
							break;
					case 2:
							assign(heads[pos],size,pos);
							break;
				}
				break;
			}
			pos++;
		}
		if(i==7){
				switch(task){
						case 1:
								insert(heads[pos],name,size,pos);
								break;
						case 2:
								assign(heads[pos],size,pos);
								break;

				}
		
		}
}
void insert(NODE *p, char *name, int a,int pos){	
		printf("This is insert 1\n");
		NODE *new;
		new=(NODE*) malloc (sizeof(NODE));//getting a new node using malloc
		if(new==NULL)//If the new node is null, we can't use it
			return;
		strcpy(new->gName,name);
		new->number=a; 
		if(p==NULL){//We insert either in head or not in another location
				p=new;
				heads[pos]=p;
				tails[pos]=new;
				tails[pos]->next=NULL;
		}
		else{
			tails[pos]->next=new;
			tails[pos]=new;
			tails[pos]->next=NULL;
		}
}

void list(){
		int i;
		for(i=0;i<4;i++){
				NODE *p=heads[i];
				while(p!=NULL){
					printf("%s: %d \n", p->gName, p->number);//prints gName and number for each nodes
					p=p->next;
				}
			}
}

int read_ch(char *ch){
		int i;
		int counter=0;
		printf("arrived at read_ch \n");
		for(i=0;i<4;i++){
				NODE *p=heads[i];
				printf("test 2 \n");
				while(p!=NULL){
						char *q=p->gName;
						while(*q!='\0'){
								printf("inside the 2nd loop \n");
								if(*q==*ch){
										counter++;
								}
								q++;
						}
						p=p->next;
				}
		}
		printf("%d occurence of %s \n",counter,ch);
		return counter;
}

void read_backwards(){
		int i;
		for(i=0;i<4;i++){
				NODE *p=heads[i];
				while(p!=NULL){
						rec_func(p->gName);
						printf("\n");
						p=p->next;		
				}
		}
}

void rec_func(char *name){
			if(*name=='\0')
					return;
			rec_func(name+1);
			printf("%c",*name);
			return;
}

void assign(NODE *p,int size,int last_place){
		int counter=0;//declaring some useful variables
		int i;
		NODE *pos=NULL;
		NODE *prePos=NULL;
		int best;
		int diff;
		int flag=0;
		NODE *q=heads[i];

		printf("arrived at assign \n");
		for(i=last_place;i>=0;i--){//This piece of code helps to find the first number to fit in the table
				if (heads[i]==NULL){
					counter++;
				}
				else{
				p=heads[i];
				q=heads[i];
				while((p->number)>size){//we loop until we find the first group to match our table
						printf("Inside while loop \n");
						if(p->next==NULL){//we break if we are at the tail because we couldn't find the match in that list
								printf("Inside if statement \n");
								q=p;
								p=p->next;
								break;
						}
						q=p;//q is recording the position before that will be helpful
						p=p->next;
				}
				}
				if(p!=NULL)
						break;
				
		}
		printf("Before counter \n");
		if(p==NULL){
				printf("There is no Costumer for this table\n");
				return;
		}
		best=size-p->number;
		printf("%d",best);
		pos=p;//keeping track of our best pos and the pos before it 
		prePos=q;
		while(p!=tails[i]){// Traverse the loop to see if there is a better fit
					diff=size-(p->number);//problem in this line
					if (diff>=0 && diff<best){
								best=diff;
								pos=p;
								prePos=q;
					}
						q=p;
						p=p->next;
				}
		if(p!=NULL){
		if((tails[i]->number<=size)&&(size-tails[i]->number<best)){//checking if the number stored in the tail is the best fit
				pos=tails[i];
				printf("%s 's group is assigned \n",pos->gName);
				tails[i]=q;
				if (tails[i]!=NULL)
						tails[i]->next=NULL;
				return;
		}
		}
		if (pos==heads[i]){//Two possibilities head and the not head
				heads[i]=heads[i]->next;
		}
		else if(pos==tails[i]){
				tails[i]=q;//This is where the problem is the q might be the same as p!
				if (tails[i]!=NULL)
						tails[i]->next=NULL;
		}
		else{
				prePos->next=pos->next;//if not head, we point from the position before to the next position and breaking the path for the node we want to remove from our list
		}
		printf("%s's group is assigned \n",pos->gName);
		if(pos==heads[i])//because the position of the array cannot be freed we set it equal to NULL instead
				heads[i]=NULL;
		if(pos==tails[i])
				tails[i]=NULL;
		if(pos!=heads[i]||pos!=tails[i]){
				free(pos);
		}//we free the  node whose path was broken
		return;
}
void * auto_save(void *filename){//This function receives the filename as a Void * and performs auto saving every 5 seconds
		char* bin_file=(char *)filename;//Casting Void* file to the type char* to open it withe the file*
		FILE *fp;
		int i;
		while(1){
				printf("Test while \n");
		pthread_mutex_lock(&mutex);//We need to lock because we don't want any changes to happen whil we open the bin_file and start saving into bin_file. 
		fp=fopen(bin_file,"wb");
		if (fp==NULL){
				printf("Can not open the binary file \n");
				return NULL;
		}
		for (i=0;i<4;i++){
				NODE *p=heads[i];
				while(p!=NULL){//Saving information from the NODE p into the address fp 
						fwrite(p,sizeof(NODE),1,fp);
						p=p->next;
				}
		}
		fclose(fp);
		pthread_mutex_unlock(&mutex);//Unlock after we are done with our saving process so that other execution can happen
		printf("Unlock \n");
		sleep(5);//Take a break from saving for 5 seconds then continue
		}
		return NULL;
}

void read_binFile(char *filename){
		FILE *fp;
		pthread_mutex_lock(&mutex);//We need to lock because if changes occur while we are reading from the binary file we will read the wrong information.
		fp=fopen(filename,"rb");
		printf("arrived at read_bin \n");
		if(fp==NULL){
				printf("Can not open the binary file \n");
				return;
		}
		NODE temp;
		//Ask Daniel about Lock and unlock
		printf("Test 2 \n");
		int ret;
		ret=fread(&temp,sizeof(NODE),1,fp);
		while(ret==1){//We loop unless there is no NODE in the file or we finished counting all the NODEs
				printf("%s \t %d",temp.gName,temp.number);//. is used to access strings or numbers because temp is the NODE not address
				ret=fread(&temp,sizeof(NODE),1,fp);
		}
		printf("Test 3 \n");
		pthread_mutex_unlock(&mutex);//After we read our information we want the user to be able to make changes 
		return;
}



