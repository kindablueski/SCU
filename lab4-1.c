// lab4 winter 2023 Xavier Zacklin
#include <stdio.h>
#include <string.h>
#include "lab4.h"

//global variables
int counter = 0;
PARTY parties[SIZE];

int main () 
{
	// creating variable to take input for switch 		
	int option;
	
	//forever loop
	while(1)
	{
		printf(" ENTER 1 to put a name down\n ENTER 2 to list all parties\n ENTER 3 to search a party by size\n ENTER 4 to seat a party by size\n Enter 0 to quit\n Enter option\n "); 
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

			case 4:
				delete();
				break;
			case 0: 
				return 0;
			default:
				printf("Wrong option\n");
		}
	}
}

void insert ()
{	
	// declaring variables to hold user input and then transfer to arrays
	char nameholder[SIZE];
	int gsizeholder;
	int dup = 0;
	int i;

	//checking if the array is already full
	if (counter == 10)
	
	{
		printf("The waiting list is full at this moment\n");
		return;	
	}
	
	//taking inputs from user
	printf("What name would you like to put your reservation under?\n");
	scanf("%s",nameholder);

	//checks if there is already a reservation under the name inputted	
	if (checkdup(nameholder) == 0)
	{
		printf("There is already a reservation under that name, Could you try a different one?\n");
		return;
	}
	
	printf("And how many people will be in your party?\n");
	scanf("%d",&gsizeholder);

	//checking if input is valid
	if (gsizeholder <= 0 ) 
	{
		printf("Please enter a valid party size\n");
		return;
	}
	
	//transfering input from user into arrays through temporary variables
	strcpy(parties[counter].name, nameholder);
	parties[counter].gsize = gsizeholder;
	counter++;
}

void show()
{	
	
	int i;
	PARTY *p = parties;

	//checking if anything is available to print
	if (counter == 0 )
	{
		printf("There are no reservations on the waiting list at this time\n");	
		return;
	}
	//printing out each value in each array
	
	for (i = 0 ; i < counter ; i++ , p++ )
	{
		printf("%s : ", p->name);
		printf("%d\n", p->gsize);
	
	}
}

void search()
{
	//declaring variables
	int temp, i;
	int flag = 0;
	PARTY *p = parties;

	//checking if their are any reservations on the waitlist	
	if (counter == 0 )
	{
		printf("The waitlist is currently empty\n");
		return;
	}
	

	//taking input to search for a specific party size
	printf("What party size are you looking for?\n");
	scanf("%d", &temp);
		for (i=0 ; i < counter ; i++, p++)
		{
	//checking for matches in the array
			if (p->gsize == temp) 
			{
				printf("%s for %d \n",p->name,p->gsize); 
				flag = 1;
			}	
		}
	//if no match is found let the user know
	if (flag == 0)
	{
		printf("No party with that size found\n");
	}
}

void delete()
{	
	//declaring variables
	int i, j;
	int gsizeholder;
	PARTY *p = parties;
	PARTY *q = parties;

	if (counter == 0 )
	{
		printf("There are no reservations on the waiting list at this moment\n");
		return;
	}
	
	
	
	// taking integer for size
	printf("For what party size is there an opening?\n");
	scanf("%d", &gsizeholder);
	
	//checking if input is valid
	if(gsizeholder <= 0 )
	{
		printf("Please enter a valid part size\n");
		return;
	}
	
	//nested for loop in order to find a reservation and shift the rest up
	for (i=0; i < counter; i++, p++)
	{
		if (gsizeholder == p->gsize)
		{
			printf("%s 's group of %d will be seated\n", p->name,p->gsize);
			for (j = i; j < counter -1 ; j++, q++)
			{
				strcpy(q->name, (q+1)->name);
				q->gsize = (q+1)->gsize;
				
			}
			counter--; 	
			return;
		}

	}
	//if there is no match in the loop let user know
	printf("There are no reservations matching that party size");

}

//function to check for duplicates
int checkdup(char dupcheck[])
{
	int i;
	int dup = 0;
	PARTY *p = parties;
	//for loop searching for equal strings between name array and input
	for (i=0; i < counter; i++ , p++)
        {
                if (strcmp(dupcheck, p->name) == 0)
                {
                        return 0;
                }
        }
	return 1;

}
