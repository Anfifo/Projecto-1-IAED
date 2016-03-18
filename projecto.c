#include <stdio.h>

#define MAX_AIRPORTS 1000
#define MAX_FLIGHTS_PER_AIRPORT 1000



typef struct
{
	char code [10];
	int capacity; /*has to be > 0*/
		
}airport;

typef struct 
{
	airport depart;
	airport arrival;
}flight;


airport airports[MAX_AIRPORTS];

int airpMatrix[MAX_AIRPORTS][MAX_AIRPORTS];


main()
{
	return 0;
}