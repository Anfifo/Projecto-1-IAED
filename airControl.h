
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
that access manage or change the airSpace */  

#include <stdio.h>
#include <string.h>

#define MAX_AIRPORTS 1000	
#define CODE_SIZE 4 		/*  3 chars + '\0'  */
#define EQUAL 0
#define OPEN 1
#define CLOSED 0
#define SUCCESS 1
#define ERROR -1




/*-- macro functions --	

we decided to use some macro functions
to avoid repeating IDcode and to make	
the IDcode more understandable 
*/


#define AIRPORT_FLIGHT_COUNT(A) (airport_flight_count_out(A) + airport_flight_count_in(A))
/* counts all the flights incoming and outgoing of airport of index A*/

#define AIRPORT_CLOSED(A) (airports[A].state == CLOSED)
/* int A => int / returns 1 if airport is closed */

#define SWAP(A,B) {A += B; B = A - B; A -= B;}
/* int A x int B => A with B's value and B with A's value */ 

#define CAPACITY_LEFT(A) (airports[A].capacity - \
		(airport_flight_count_out(A) + airport_flight_count_in(A)))
/* int A => int 	/returns airport A's free capacity */ 






/* -- structures -- */
	
typedef struct
{
	char IDcode [CODE_SIZE];	/* 3 chars + '\0' 								   */
	int capacity; 			/* int > 0  (how many flights an airport can have) */
	int state; 				/* OPEN or CLOSED 								   */
	int index; 				/* ERROR if undefined 							   */
}airport;




typedef struct 
{ /* a pair of airport indexes */
	int out;
	int in;
}flight;







/* -- global variables --

we defined as extern as we'll link 
their actual value on the .c file

while we know it's best not to use global variables, 
it was sugested that we did for this project  */

extern airport airports[MAX_AIRPORTS];
/* vector with all defined and undefined airports */

extern int airSpace[MAX_AIRPORTS][MAX_AIRPORTS];
/* Matrix that defines the airSpace, where the coordinates 
are [outgoing airport's index] [incoming airport's index] and 
the value it contains is the number of flights from [out] to [in] */

extern int nr_of_airports;
/* is updated everytime a new airport is added limited by MAX_AIRPORTS*/

extern int total_flight_count;
/* contains all the flights in airSpace, is update whenever a flight is added */

extern int max_airport_capacity;
/* contains and is updated with the max capacity given to an airport*/










/* -- Auxiliar Functions -- */

int IDcode_to_index(char IDcode[]);
/*
* finds the index of the aiport with given IDcode 
* :: argmts: char [] -- an airport's IDcode
* :: return: int -- airport's index
*/

flight IDcodes_to_flight(char IDcode1[], char IDcode2[]);
/*
* finds the indexes of the 2 airport IDcodes and creates it's flight.
* :: argmts: char[], char[] -- 2 airport IDcodes
* :: return: flight -- from IDcode1's aiport to IDcode2's airport
*/




/* -- Flights --*/

flight create_flight (int out, int in);
/*
* creates a flight type from  int out to int in 
* :: argmts: int, int -- 2 airport indexes
* :: return: flight -- from out's airport to in's airport
*/





/* -- Airports -- */

/* MODIFIERS */
int add_airport(char IDcode[], int capacity);
/*
* modifies airports global vector to adds airport with given IDcode and 
* capacity, adds 1 to the global counter of airports
* :: argmts: char [], int -- airport's IDcode and capacity
* :: return: int -- SUCESS if added else, ERROR
*/

int modify_capacity(int index, int change);
/*
* modifies given index airport's capacity by a 'change' amount
* :: argmts: int, int -- airport's index and change for capacity
* :: return: int -- SUCCESS if change happen else, ERROR
*/

int close_airport(int index);
/*
* changes aiport's state to CLOSED and removes all inc and outg flights
* :: argmts: int -- airport's index
* :: return: int -- SUCCESS if change happen else, ERROR
*/

int open_airport(int index);
/*
* changes airport's state to OPEN
* :: argmts: int -- aiport's index
* :: return: int -- SUCCESS if change happen else, ERROR
*/





/* -- AirSpace -- */

void initialize_airSpace();
/*
* initializes airSpace Matrix with zeros and 
* all airports in airports vector as undefined 
* :: argmts: --
* :: return: --
*/

/* MODIFIERS */

int add_flight(flight fl);
/*
* modifies airpSpace to adds flight, increases by 1 the global flight counter
* :: argmts: flight -- to be added to airSpace
* :: return: int -- SUCESS/ERROR
*/

int remove_flight(flight fl);
/*
* modifies airSpace to remove flight, decreases by 1 the global flight counter
* :: argmts: flight -- to be removed from airSpace
* :: return: int -- SUCCESS/ERROR
*/

int add_round_trip(flight fl);
/*
* modifies airSpace to add 2 flights one going and another coming back,
* increases by 2 the global flight counter
* :: argmts: flight -- to be added to airSpace
* :: return: int -- SUCCESS/ERROR
*/

int remove_round_trip(flight fl);
/*
* modifies airSpace to remove 2 flights one going and another coming back,
* decreases by 2 the global flight counter
* :: argmts: flight -- to be removed from airSpace
* :: return: int -- SUCESS/ERROR
*/


/* SELECTORS */
int flight_count(flight fl);
/*
* accesses airSpace to see the sum of flights fl in the airspace (same inc-out)
* :: argmts: flight --
* :: return: int -- number of flights fl(with same departure-destination)
*/

int airport_flight_count_out(int index);
/*
* finds and sums all the outgoing flights from airport
* :: argmts: index -- aiport's index
* :: return: int -- sum of all outgoing flights or error if undefined airport
*/

int airport_flight_count_in(int index);
/*
* finds and sums all the incoming flights to airport
* :: argmts: int -- aiport's index
* :: return: int -- sum of all incoming flights or error if undefined airport
*/

int airport_connection_count(int index);
/*
* find and sums how many other airports index's airport is connected to
* :: argmts: int -- airport's index 
* :: return: int -- sum of all aiport's connections
*/


int most_flights();
/*
* finds the airport with the highest number of flights (incoming+outgoing)
* :: argmts: --
* :: return: int -- the index of the airport with highest nr of flights 
*/

int most_connections();
/*
* find the aiport with the highest number of connections 
* :: argmts: --
* :: return: int -- the index of the airport with highest nr of connections
*/

flight most_popular_flight();
/*
* caculates the max of flight counts (the most common/popular flight) 
* :: argmts: --
* :: return: flight -- the most popular flight (with highest count)
*/


/* OUTPUT */
void print_index_order();
/*
* prints airport's IDcode capacity and flight counts (in & out) by index order
* :: argmts: --
* :: return: --
*/

void sort_alphabetical(int array[]);
/*
* sorts the airport's IDcodes alphabetically by saving their indexes in array[]
* in alphabetical-sorted order
* :: argmts: --
* :: return: --
*/

void print_alphabetical_order();
/*
* prints airport's in alphabetical order
* :: argmts: --
* :: return: --
*/

void print_histogram();
/*
* prints k:d(k) being k the number of flights and 
* d(k)the number of airports with k flights
* :: argmts: --
* :: return: --
*/




