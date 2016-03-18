#include <stdio.h>

#define MAX_AIRPORTS 1000
#define MAX_FLIGHTS_PER_AIRPORT 1000
#define CODE_SIZE 3


/* types */
typedef struct
{
	char code [10];
	int capacity; /*has to be > 0*/
	int state;
	int index;
}airport;


typedef struct 
{
	airport depart;
	airport arrival;

}flight;



/* global variables */
airport airports[MAX_AIRPORTS];
int airpMatrix[MAX_AIRPORTS][MAX_AIRPORTS];
int next_airport_index = 0;

/* auxiliar functions */

void copy_codes(char target[], char code[])
{
	int i;
	for (i = 0; i < CODE_SIZE; i++)
		target[i] = code [i];
	target[i+1] = '\0';
}

int compare_codes(char code1[], char code2[])
{
	int i;

	for( i = 0; i < CODE_SIZE; i++)
	{
		if (code1[i] != code2[i])
			return 0;
	}
	return 1;
}

int code_to_index(char code[])
{
	int i;
	for (i = 0; i < next_airport_index; i++)
	{
		if (compare_codes(airports[i].code, code))
			return airports[i].index;
	}
	return -1;
}


/* type functions */

void create_airport(char code[], int capa)
{
	int index = next_airport_index;
	copy_codes(airports[index].code, code);

	airports[index].capacity = capa;  
	airports[index].index = index;
	next_airport_index++;
}





void menu()
{
	while (1)
	{
		switch (c = getchar() )
		{
			case 'A':
			
				break;
				
			case 'I':
			
				break;
				
			case 'F':
			
				break;
				
			case 'G':
			
				break;
				
			case 'R':
			
				break;
				
			case 'S':
			
				break;
				
			case 'N':
			
				break;
				
			case 'P':
			
				break;
				
			case 'Q':
			
				break;
			
			case 'U':
			
				break;
				
			case 'C':
			
				break;

main()
{
	return 0;
}
