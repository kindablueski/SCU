// lab4 winter 2023 Xavier Zacklin
#include <stdio.h>
#include <string.h>
#define SIZE 10

//declaring global structure
typedef struct party {
	int gsize;
	char name[SIZE];
} PARTY;

extern PARTY gsize;
extern PARTY name[SIZE];

//declaring functions

void insert(void);
void show(void);
void search(void);
void delete(void);
int checkdup(char nameholder[]);

