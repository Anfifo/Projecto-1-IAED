
/* 
== = = = = = = = = = = ==
= /////// tg034 /////// =
== = = = = = = = = = = ==
=  84698 Andre Fonseca	=
=  84726 Isabel Dias	=
== = = = = = = = = = = ==
=  1o Projecto de IAED	=
=   LEIC-T 2015-2016	=
== = = = = = = = = = = == 
*/

/* this header contains all the headers and functions 
that access mannage or change the airSpace */  


#include <stdio.h>
#include <string.h>

#define MAX_AIRPORTS 1000
#define CODE_SIZE 4

#define EQUAL 0
#define OPEN 1
#define CLOSED 0
#define SUCCESS 1
#define ERROR -1

#define FLIGHT_COUNT(A) (airport_flight_count_out(A) + airport_flight_count_in(A))
#define AIRPORT_CLOSED(A) (airports[A].state == CLOSED)
#define SWAP(A,B) {A += B; B = A - B; A -= B;}

#define CAPACITY_LEFT(A) (airports[A].capacity - \
		(airport_flight_count_out(A) + airport_flight_count_in(A)))


/*  == == == == == == == ==
	= Types and variables =
	== == == == == == == ==  */
	
typedef struct
{
	char code [CODE_SIZE]; /* or ID */
	int capacity; /*has to be > 0*/
	int state; /*open - 1; closed - 0*/
	int index; /* -1 if undefined */
}airport;


typedef struct 
{ /* a pair of airport indexes */
	int out;
	int in;
}flight;


/* global variables */

airport airports[MAX_AIRPORTS];
int airSpace[MAX_AIRPORTS][MAX_AIRPORTS];
int nr_of_airports = 0;
int total_flight_count = 0;
int max_airport_capacity = 0;



/*
	== == == == == == == ==
	=      Prototypes     =
	== == == == == == == ==  */

/* ____Flights____ */

flight create_flight (int out, int in);


/* ____Airports____ */

int modify_capacity(int index, int change);
int close_airport(int index);
int open_airport(int index);


/* ____AirSpace___ */

int add_airport(char code[], int capa);
int add_flight(flight fl);
int remove_flight(flight fl);
int add_round_trip(flight fl);
int remove_round_trip(flight fl);

int flight_count(flight fl);
int airport_flight_count_out(int index);
int airport_flight_count_in(int index);
int airport_connection_count(int index);
flight most_popular_flight();
int most_flights();
int most_connections();

void print_index_order();
void sort_alphabetical(int array[]);
void print_alphabetical_order();
void print_histogram();






/*  == == == == == == == == ==
	=   Auxiliar Functions   =
	== == == == == == == == ==  */


int code_to_index(char code[])
{ /* returns the index of an airport
	based on its code/id */
	int i;
	for (i = 0; i < nr_of_airports; i++)
		if ((airports[i].index != ERROR) &&
			(strcmp(airports[i].code, code) == EQUAL))
				return airports[i].index;

	return ERROR;
}


flight codes_to_flight(char code1[], char code2[])
{ /* creates a flight from 2 airport codes */
	int index1 = code_to_index(code1);
	int index2 = code_to_index(code2);
	flight fl = create_flight(index1, index2);

	return fl;
}


/*  == == == == == == == ==
	=  Flight Functions   =
	== == == == == == == ==  */

flight create_flight (int out, int in)
{/* creates a flight from 2 airport indexes */
	flight fl;
	fl.out = out;
	fl.in = in;
	return fl;
}



/*  == == == == == == == ==
	=  Airports Functions =
	== == == == == == == ==  */

int open_airport(int index)
{ /* opens index's airport */

	if (index == ERROR) 	
		return ERROR;

	airports[index].state = OPEN;
	return SUCCESS;
}


int close_airport(int index)
{ /* closes index's airport */
	int i;
	
	if (index == ERROR)
		return ERROR;

	/* removes all flights from and to airport*/
	for (i = 0; i < nr_of_airports; i++)
	{
		total_flight_count -= airSpace[index][i];
		total_flight_count -= airSpace[i][index];
		airSpace[index][i] = 0;
		airSpace[i][index] = 0;
	}
	
	airports[index].state = CLOSED;
	return SUCCESS;
}

int  modify_capacity(int index, int change)
{ /* modifies the capacity of index's airport */
	int old_capacity = airports[index].capacity;
	int new_capacity = old_capacity + change;

	if (index == ERROR || new_capacity < 0 ||
		FLIGHT_COUNT(index) > new_capacity ||
		AIRPORT_CLOSED (index))
			return ERROR;

	airports[index].capacity = new_capacity;

	if (new_capacity > max_airport_capacity)
		max_airport_capacity = new_capacity;
	
	return SUCCESS;
}


/*  == == == == == == == == ==
	=   AirSpace Functions   =
	== == == == == == == == ==  */


/* ____MODIFIERS____ */

int add_airport(char code[], int capa)
{ /* adds an airport to the airportList*/
	int index = nr_of_airports;	

	if (capa <= 0)
		return ERROR;

	airports[index].capacity = capa;
	airports[index].state = OPEN;
	airports[index].index = index;
	strcpy(airports[index].code, code);

	nr_of_airports++;
	if (capa > max_airport_capacity)
		max_airport_capacity = capa;

	return SUCCESS;
}


int add_flight(flight fl)
{ /* adds a flight to airSpace */
	if (fl.out == ERROR ||
		fl.in == ERROR ||
		AIRPORT_CLOSED(fl.out) ||
		AIRPORT_CLOSED(fl.in) ||
		CAPACITY_LEFT(fl.out) < 1 ||
		CAPACITY_LEFT(fl.in) < 1)
			return ERROR;

	airSpace[fl.out][fl.in]++;
	total_flight_count++;
	return SUCCESS;
}


int remove_flight(flight fl)
{ /* removes a flight from the airSpace */
	if (fl.out == ERROR || fl.in == ERROR || 
		AIRPORT_CLOSED(fl.out) || AIRPORT_CLOSED(fl.in) ||
		flight_count(fl) < 1)
			return ERROR;

	airSpace[fl.out][fl.in]--;
	total_flight_count--;
	
	return SUCCESS;
}


int add_round_trip(flight fl)
{ /* adds an outgoing and an incoming 
	 flights between the airports */

	if (fl.out == ERROR || fl.in == ERROR ||
		AIRPORT_CLOSED(fl.out) || AIRPORT_CLOSED(fl.in) ||
		CAPACITY_LEFT(fl.out) < 2 || CAPACITY_LEFT(fl.in) < 2)
			return ERROR;

	airSpace[fl.out][fl.in]++;
	airSpace[fl.in][fl.out]++;
	total_flight_count += 2;

	return SUCCESS;
}


int remove_round_trip(flight fl)
{ /* removes an outgoing and an incoming
	 flights between the aiports */
	flight RT_fl = create_flight(fl.in, fl.out);

	if (fl.out == ERROR || fl.in == ERROR ||
		AIRPORT_CLOSED(fl.out) || AIRPORT_CLOSED(fl.in) ||
		flight_count(fl) < 1 || flight_count(RT_fl) < 1)
			return ERROR;

	airSpace[fl.out][fl.in]--;
	airSpace[fl.in][fl.out]--;
	total_flight_count -= 2;

	return SUCCESS;
}




/* ____SELECTORS____ */

int flight_count(flight fl)
{
	if (fl.out == ERROR || fl.in == ERROR)
		return ERROR;

	return airSpace[fl.out][fl.in];	
}


int airport_flight_count_out(int index)
{ /* returns the number of outgoing flights at index's airport */
	int i, count = 0;

	if (index == ERROR)
		return ERROR;

	for(i = 0; i < nr_of_airports; i++)
		count += airSpace[index][i];	

	return count;
}


int airport_flight_count_in(int index)
{ /* returns the number of incoming flights at index's airport */
	int i, count = 0;

	if (index == ERROR)
		return ERROR;
	
	for(i = 0; i < nr_of_airports; i++)
		count += airSpace[i][index];	
	
	return count;
}


int airport_connection_count(int index)
{ /* returns the number of connected airports to index's airport */ 
	int i, count = 0;

	if (index == ERROR)
		return ERROR;
	
	for (i = 0; i < nr_of_airports; i++)
		if (airSpace[index][i] > 0 || airSpace[i][index] > 0)
			count++;

	return count;
}


int most_flights()
{ /* returns the airport's index with most flights */
	int index;
	int count = 0;
	int max = 0;
	int max_index = 0;
	
	for(index = 0; index < nr_of_airports; index++)
	{
		count = airport_flight_count_in(index) + 
				airport_flight_count_out(index);
		
		if (count > max)
		{
			max = count;
			max_index = index;
		}		
	}
	return max_index;
}


int most_connections()
{ /* returns the airport's index with most connections */
	int index;
	int count = 0;
	int max = 0;
	int max_index = 0;
	
	for(index = 0; index < nr_of_airports; index++)
	{
		count = airport_connection_count(index);
		
		if (count > max)
		{
			max = count;
			max_index = index;
		}		
	}
	return max_index;
}


flight most_popular_flight()
{ /* returns the most popular flight */
	int out = 0, in = 0, max = 0;
	flight max_flight;
	
	for (out = 0; out < nr_of_airports; out++)
		for (in = 0; in < nr_of_airports; in++)
			if (airSpace[out][in] > max)
			{		
				max = flight_count(create_flight(out,in));
				max_flight.out = out;
				max_flight.in = in;
			}	
	return max_flight;
}






/*  == == == == == == == ==
	=   Output Functions  =
	== == == == == == == ==  */

void print_index_order()
{ /* prints by index order in vector */
	int i, in, out;
	
	for (i = 0; i < nr_of_airports; i++)
	{
		out = airport_flight_count_out(i);
		in = airport_flight_count_in(i);
		
		printf("%s:%d:%d:%d\n",
				airports[i].code, 
				airports[i].capacity, 
				out, in);
	}
}


void sort_alphabetical(int array[])
{ /* modifies an input array that sorts 
	the airports' indexes alphabetically*/
	int i, j;
	
	/* initializes the array in index's order */
	for (i = 0; i < nr_of_airports; i++)
		array [i] = i;

	for ( i = 0; i < nr_of_airports; i++)
		for ( j = i+1; j < nr_of_airports; j++)
			if (strcmp(airports[array[i]].code, airports[array[j]].code) > 0) 
				SWAP(array[i], array[j]);
}
			
	
void print_alphabetical_order()
{/* prints the airports alphabetically sorted */
	int i;
	int array[nr_of_airports];
	
	sort_alphabetical(array);
	
	for (i = 0; i < nr_of_airports; i++)
	{
		int out = airport_flight_count_out(array[i]);
		int in = airport_flight_count_in(array[i]);
		
		printf("%s:%d:%d:%d\n", 
				airports[array[i]].code, 
				airports[array[i]].capacity, 
				out, in);
	}
}

void print_histogram()
{/* prints the nr of airports
	that have the same nr of flights */ 
	int i;
	int array[max_airport_capacity+1];
	for ( i = 0; i < (max_airport_capacity+1); i++)
		array[i] = 0;

	/* puts in position array's i position
	the number of airports with i flights */
	for (i = 0; i < nr_of_airports; i++)
		array[FLIGHT_COUNT(i)]++;
	
	i = 0;
	/* prints the previous array */
	while (i < max_airport_capacity+1) /* born to be while */
	{
		if (array[i] != 0)
			printf("%d:%d\n", i, array[i]);
		i++;
	}
}
