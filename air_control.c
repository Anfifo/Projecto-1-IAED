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


#include "air_control.h"




/* -- global variables -- */
airport airports[MAX_AIRPORTS];
int airSpace[MAX_AIRPORTS][MAX_AIRPORTS];
int nr_of_airports = 0;
int total_flight_count = 0;
int max_airport_capacity = 0;







/*  == == == == == == == == ==
	=   Auxiliar Functions   =
	== == == == == == == == ==  */

int IDcode_to_index(char IDcode[])
{ /* returns the index of an airport
	based on its IDcode/id */
	int i;
	for (i = 0; i < nr_of_airports; i++)
		if ((airports[i].index != ERROR) &&
			(strcmp(airports[i].IDcode, IDcode) == EQUAL))
				return airports[i].index;

	return ERROR;
}


flight IDcodes_to_flight(char IDcode1[], char IDcode2[])
{ /* creates a flight from 2 airport IDcodes */
	int index1 = IDcode_to_index(IDcode1);
	int index2 = IDcode_to_index(IDcode2);
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

int add_airport(char IDcode[], int capacity)
{ /* adds an airport to the airportList*/
	int index = nr_of_airports;	

	if (capacity <= 0)
		return ERROR;

	airports[index].capacity = capacity;
	airports[index].state = OPEN;
	airports[index].index = index;
	strcpy(airports[index].IDcode, IDcode);

	nr_of_airports++;
	if (capacity > max_airport_capacity)
		max_airport_capacity = capacity;

	return SUCCESS;
}

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
		AIRPORT_FLIGHT_COUNT(index) > new_capacity ||
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

void initialize_airSpace()
{/* initializes airpace with zero flights
	and all airports as undefined (ERROR index)*/
	int i,j;
	for (i = 0; i < MAX_AIRPORTS; i++)
	{	
		for (j = 0; j < MAX_AIRPORTS; j++)
			airSpace[i][j] = 0;
		airports[i].index = ERROR;
	}
}


/* -- MODIFIERS -- */

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
	flight reverse_fl = create_flight(fl.in,fl.out);
	if (fl.out == ERROR || fl.in == ERROR ||
		AIRPORT_CLOSED(fl.out) || AIRPORT_CLOSED(fl.in) ||
		CAPACITY_LEFT(fl.out) < 2 || CAPACITY_LEFT(fl.in) < 2)
			return ERROR;

	add_flight(fl);
	add_flight(reverse_fl);

	return SUCCESS;
}


int remove_round_trip(flight fl)
{ /* removes an outgoing and an incoming
	 flights between the aiports */
	flight reverse_fl = create_flight(fl.in, fl.out);

	if (fl.out == ERROR || fl.in == ERROR ||
		AIRPORT_CLOSED(fl.out) || AIRPORT_CLOSED(fl.in) ||
		flight_count(fl) < 1 || flight_count(reverse_fl) < 1)
			return ERROR;

	remove_flight(fl);
	remove_flight(reverse_fl);

	return SUCCESS;
}




/* -- SELECTORS -- */

int flight_count(flight fl)
{/* returns the number of flights with the
	same destination and departure */
	if (fl.out == ERROR || fl.in == ERROR)
		return ERROR;

	return airSpace[fl.out][fl.in];	
}







/*  == == == == == == == == ==
	=    General Functions   =
	== == == == == == == == ==  */

int airport_flight_count_out(int index)
{ /* returns the number of outgoing flights at index's airport */
	int i, count = 0;

	if (index == ERROR)
		return ERROR;

	for(i = 0; i < nr_of_airports; i++)
		count += flight_count(create_flight(index, i));	

	return count;
}


int airport_flight_count_in(int index)
{ /* returns the number of incoming flights at index's airport */
	int i, count = 0;

	if (index == ERROR)
		return ERROR;
	
	for(i = 0; i < nr_of_airports; i++)
		count += flight_count(create_flight(i, index));	
	
	return count;
}


int airport_connection_count(int index)
{ /* returns the number of connected airports to index's airport */ 
	int i, count = 0;

	if (index == ERROR)
		return ERROR;
	
	for (i = 0; i < nr_of_airports; i++)
		if (flight_count(create_flight(index,i)) > 0 ||
		 	flight_count(create_flight(i,index)) > 0)
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
		count = AIRPORT_FLIGHT_COUNT(index);
		
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
	int out, in, max = 0, count = 0;
	flight max_flight;
	
	for (out = 0; out < nr_of_airports; out++)
		for (in = 0; in < nr_of_airports; in++)
		{
			count = flight_count(create_flight(out, in));
			
			if (count > max)
			{
				max = count;
				max_flight = create_flight(out, in);
			}
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
				airports[i].IDcode, 
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
			if (strcmp(airports[array[i]].IDcode, airports[array[j]].IDcode) > 0) 
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
				airports[array[i]].IDcode, 
				airports[array[i]].capacity, 
				out, in);
	}
}

void print_histogram()
{/* prints the nr of airports
	that have the same nr of flights */ 
	int i;
	int flights = 0;
	int sum_of_flights = 0;
	int airport_count = 0;
	int array[max_airport_capacity+1];

	/* initializing array with zeros */
	for ( i = 0; i < (max_airport_capacity + 1); i++)
		array[i] = 0;

	/* adds to array's i position the 
	number of airports with i flights */
	for (i = 0; i < nr_of_airports; i++)
		array[AIRPORT_FLIGHT_COUNT(i)]++;
	
	/* prints the previous array*/
	while (sum_of_flights < (total_flight_count*2))  /* born to be while */
	{	
		airport_count = array [flights];
		
		if (airport_count != 0)
		{	
			sum_of_flights += (flights * airport_count);
			printf("%d:%d\n", flights, airport_count);
		}
		flights++;
	}	
}
