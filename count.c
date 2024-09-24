// global library

#include <stdio.h>

//define statements for global values

#define MAXLENGTH 30

//function prototypes
void countwords(char* filename);

//function to count how many words are in each file, takes in the name of the file as an argument 


void countwords(char *filename){

//declaring variables for the algorithim

	FILE *fp;
	int counter = 0;
	char word[30];

//opening the file and checking if it exists

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error: Unable to open file\n");
		return;
	}

//scan each word from the text file and increase counter until there is no more words to scan
		
	while (fscanf(fp, "%s", word) == 1) 
	{
		counter++;	
	}

//close the pointer return and output the amount of words in each text file	
	fclose (fp);
	printf ("Word Count : %d \n ", counter);
	return;
}
//main function to pass in object and amount object being the file
int main(int argc, char *argv[]){
	
	countwords(argv[1]);
	return 0;

}
