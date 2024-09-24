// lab1 winter 2023 Xavier Zacklin
#include <stdio.h>
#include <string.h>

#define SIZE 10

//global variables
int counter = 0;
char name[SIZE][SIZE];
int gsize[SIZE]; 

//declaring functions
void insert(void);
void show(void);
void search(void);

int main () 
{
	// creating variable to take input for switch 		
	int option;
	
	//forever loop
	while(1)
	{
		printf(" ENTER 1 to put a name down\n ENTER 2 to list all parties\n ENTER 3 to search a party by size\n ENTER 0 to quit\n enter option\n"); 
		scanf("%d",&option);	
		switch (option)
		{
			case 1:
				insert();	
				break;
			
			case 2:
				show();
				break;

			case 3:
				search();
				break;

			case 0: 
				return 0;
			default:
				printf("wrong option\n");
		}
	}
}

void insert ()
{	
	// declaring variables to hold user input and then transfer to arrays
	char nameholder[SIZE];
	int gsizeholder;
 	
	//checking if the array is already full
	if (counter == 10)
	
	{
		printf("The waiting list is full at this moment\n");
		return;	
	}
	
	//taking inputs from user
	printf("What name would you like to put your reservation under?\n");
	scanf("%s",nameholder);
	printf("And how many people will be in your party?\n");
	scanf("%d",&gsizeholder);

	//checking if input is valid
	if (gsizeholder <= 0 ) 
	{
		printf("Please enter a valid party size\n");
		return;
	}
	
	//transfering input from user into arrays through temporary variables
	strcpy(name[counter], nameholder);
	gsize[counter] = gsizeholder;
	printf("%s's party for %d has been added to the list\n" , nameholder, gsizeholder);
	counter++;
}

void show()
{
	if (counter == 0)
	{
		printf("There currently are no reservations\n");
		return;
	}

	//printing out each value in each array
	int i;
	for (i = 0 ; i < counter ; i++)
	{
		printf("%s : ", name[i]);
		printf("%d\n", gsize[i]);
	
	}
}

void search()
{
	//checking if their are any reservations on the waitlist	
	if ( counter == 0 )
	{
		printf("The waitlist is currently empty\n");
		return;
	}

	//declaring variables
	int temp, i;
	int flag = 0;
	
	//taking input to search for a specific party size
	printf("What party size are you looking for?\n");
	scanf("%d", &temp);
		for (i=0 ; i < counter ; i++)
		{
	//checking for matches in the array
			if (gsize[i] == temp) 
			{
				printf("%s at %d PM\n",name[i],gsize[i]); 
				flag = 1;
			}	
		}
	//if no match is found let the user know
	if (flag == 0)
	{
		printf("No party with that size found\n");
	}
}
