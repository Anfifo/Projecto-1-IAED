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

#include <stdio.h>

#define MAX_AIRPORTS 1000
#define CODE_SIZE 4

#define EQUAL 0
#define GREATER 1
#define SMALLER -1

#define OPEN 1
#define CLOSED 0

#define SUCCESS 1
#define ERROR -1

#define FLIGHT_COUNT(A) (airport_flight_count_out(A) + airport_flight_count_in(A))
#define CAPACITY_LEFT(A) (airports[A].capacity - (airport_flight_count_out(A) + airport_flight_count_in(A)))
#define AIRPORT_CLOSED(A) (airports[A].state == CLOSED)

/*  == == == == == == == ==
	= Types and variables =
	== == == == == == == ==  */
typedef struct
{
	char code [CODE_SIZE];
	int capacity; /*has to be > 0*/
	int state; /*on - 1; off - 0*/
	int index;
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



/* Type Functions */
flight create_flight (int out, int in);
flight codes_to_flight(char code1[], char code2[]);
/* Main Functions */
int add_airport(char code[], int capa);
int modify_capacity(int index, int change);
int add_round_trip(flight fl);
int remove_round_trip(flight fl);
int add_flight(flight fl);
int remove_flight(flight fl);
int flight_count(flight fl);
int airport_flight_count_out(int index);
int airport_flight_count_in(int index);
int airport_connection_count(int index);
int most_flights();
int most_connections();
flight most_popular_flight();
int close_airport(int index);
int open_airport(int index);
void print_index_order();
void sort_alphabetical(int array[]);
void print_alphabetical_order();
void print_histogram();
/* Commands */
void command_A();
void command_I();
void command_F();
void command_G();
void command_R();
void command_S();
void command_N();
void command_P();
void command_Q();
void command_V();
void command_C();
void command_O();
void command_L();
int menu();
int main();





/*  == == == == == == == == ==
	=   Auxiliar Functions   =
	== == == == == == == == ==  */

void copy_codes(char target[], char code[])
{
	int i;
	for (i = 0; i < CODE_SIZE; i++)
		target[i] = code [i];
	target[i+1] = '\0';
}


int compare_codes(char code1[], char code2[])
{ /* compares 2 strings, if they're bigger, smaller or equal */
	int i;

	while (code2[i] != '\0' && code1[i] != '\0')
	{
		if (code1[i] < code2[i])
			return SMALLER;
			
		else if (code1[i] > code2[i])
			return GREATER;	
		
		i++;
	}
	return EQUAL;
}


int code_to_index(char code[])
{
	int i;
	
	for (i = 0; i < nr_of_airports; i++)
	{
		if ((airports[i].index != ERROR) &&
			(compare_codes(airports[i].code, code) == EQUAL))
				return airports[i].index;
	}
	return ERROR;
}



/*  == == == == == == == ==
	=    Type Functions   =
	== == == == == == == ==  */



/* flight */
flight create_flight (int out, int in)
{
	flight fl;
	fl.out = out;
	fl.in = in;
	return fl;
}

flight codes_to_flight(char code1[], char code2[])
{	
	int index1 = code_to_index(code1);
	int index2 = code_to_index(code2);
	flight fl = create_flight(index1, index2);

	return fl;
}

/*  == == == == == == == ==
	=    Main Functions   =
	== == == == == == == == */


int add_airport(char code[], int capa)
{	
	int index = nr_of_airports;	

	if (capa <= 0)
		return ERROR;

	airports[index].capacity = capa;
	airports[index].state = OPEN;
	airports[index].index = index;
	copy_codes(airports[index].code, code);

	nr_of_airports++;
	return SUCCESS;
}


int  modify_capacity(int index, int change)
{	/* modifies the capacity of index's airport */
	int old_capacity = airports[index].capacity;
	int new_capacity = old_capacity + change;

	if (index == ERROR || FLIGHT_COUNT(index) > new_capacity)
	{
		return ERROR;
	}

	airports[index].capacity = new_capacity;

	if (airports[index].capacity > max_airport_capacity)
		max_airport_capacity = airports[index].capacity;
	
	return SUCCESS;
}


/* flights */

int add_round_trip(flight fl)
{/* adds 2 flights one incoming and
	one outgoing to both airports */

	if (fl.out == ERROR ||
		fl.in == ERROR ||
		AIRPORT_CLOSED(fl.out) ||
		AIRPORT_CLOSED(fl.in) ||
		CAPACITY_LEFT(fl.out) < 2 ||
		CAPACITY_LEFT(fl.in) < 2)
		return ERROR;

	airSpace[fl.out][fl.in]++;
	airSpace[fl.in][fl.out]++;
	
	total_flight_count += 2;

	return SUCCESS;
}

int remove_round_trip(flight fl)
{/* removes 2 flights one incoming and
	one outgoing to both aiports */
	if (fl.out == ERROR || fl.in == ERROR)
		return ERROR;

	airSpace[fl.out][fl.in]--;
	airSpace[fl.in][fl.out]--;
	total_flight_count -= 2;

	return SUCCESS;
}

int add_flight(flight fl)
{
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
{
	if (fl.out == ERROR || fl.in == ERROR)
		return ERROR;

	airSpace[fl.out][fl.in]--;
	total_flight_count--;
	
	return SUCCESS;
}

int flight_count(flight fl)
{	
	if (fl.out == ERROR || fl.in == ERROR)
		return ERROR;

	return airSpace[fl.out][fl.in];	
}



/* airports */

int airport_flight_count_out(int index)
{ /* returns the number of outcoming flights at index's airport*/
	int i, count = 0;

	for(i = 0; i < nr_of_airports; i++)
		count += airSpace[index][i];	

	return count;
}

int airport_flight_count_in(int index)
{ /* returns the number of incoming flights at index's aiport */
	int i, count = 0;
	
	for(i = 0; i < nr_of_airports; i++)
		count += airSpace[i][index];	
	
	return count;
}


int airport_connection_count(int index)
{ /* returns the number of connected airports to index's airport */ 
	int i, count = 0;
	
	for (i = 0; i < nr_of_airports; i++)
		if (airSpace[index][i] > 0 || airSpace[i][index] > 0)
			count++;

	return count;
}



/* general */
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
	{
		for (in = 0; in < nr_of_airports; in++)
		{
			if (airSpace[out][in] > max)
			{		
				max = flight_count(create_flight(out,in));
				max_flight.out = out;
				max_flight.in = in;
			}	
		}
	}
	return max_flight;
}


int close_airport(int index)
{ /* closes index's airport */
	int i;
	
	if (index == ERROR)
		return ERROR;

	for (i = 0; i < nr_of_airports; i++)
	{
		airSpace[index][i] = 0;
		airSpace[i][index] = 0;
	}
	
	airports[index].state = CLOSED;
	return SUCCESS;
}


int open_airport(int index)
{ /* OPENS de airport of a certain index */

	if (index == ERROR) 	
		return ERROR;

	airports[index].state = OPEN;
	return SUCCESS;
}



/* Related to command L*/
void print_index_order()
{
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
{
	int i, j, value;
	
	for ( i = 0; i < nr_of_airports; i++)
	{	
		for ( j = i+1; j < nr_of_airports; j++)
		{	
			array[j] = j;
				
			if ((value = compare_codes(airports[i].code, airports[j].code) == GREATER)) 
				array[i] = j;
			else 
				array[i] = i;
		}
	}
}
			
	

void print_alphabetical_order()
{
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
{
	int i, j;
	int count_out;
	int count_in;
	int array[max_airport_capacity+1];
	
	for (i = 0; i < nr_of_airports; i++)
	{
		count_out = airport_flight_count_out(airports[i].index);
		count_in = airport_flight_count_in(airports[i].index);
		array[count_in+count_out]++;
	}
	
	i = 0;
	j = 0;
	
	while (i < total_flight_count) /*born to be while*/
	{
		if (array[j] != 0)
		{
			printf("%d:%d\n", j, array[j]);
			i += j;
		}	
		j++;
	}
}





/*  == == == == == == ==
	=     Commands     =
	== == == == == == == */

void command_A()
{ /* adds an airport */
	char code[CODE_SIZE];
	int capa;

	puts("add airport");
	scanf("%s %d", code, &capa);
	add_airport(code, capa);
}

void command_I()
{ /* changes an airport's capacity*/
	char code [CODE_SIZE];
	int new_capacity, index;

	puts("modify airport capacity");
	scanf("%s %d", code, &new_capacity);
	index = code_to_index(code);

	if ( modify_capacity(index, new_capacity) == ERROR)
		printf("*Capacidade de %s inalterada\n",code);
		
}

void command_F()
{ /* adds a roundtrip flight */
	char code1 [CODE_SIZE];
	char code2 [CODE_SIZE];
	puts("add round trip");
	scanf("%s %s", code1, code2);

	flight fl = codes_to_flight(code1,code2);
	
	if (add_round_trip(fl) == ERROR)
		printf("*Impossivel adicionar voo RT %s %s\n", code1, code2);
}

void command_G()
{ /* adds a single flight */ 
	char code1 [CODE_SIZE];
	char code2 [CODE_SIZE];

	puts("add flight");
	scanf("%s %s", code1, code2);
	
	flight fl = codes_to_flight(code1, code2);

	if (add_flight(fl) == ERROR)
		printf("*Impossivel adicionar voo %s %s\n", code1, code2);
}

void command_R()
{ /*removes a flights */
	char code1 [CODE_SIZE];
	char code2 [CODE_SIZE];
	puts("remove flight");
	scanf("%s %s", code1, code2);
	
	flight fl = codes_to_flight(code1, code2);

	if (remove_flight(fl) == ERROR)
		printf("*Impossivel remover voo %s %s\n", code1, code2);
}

void command_S()
{ /* removes a roundtrip flights */
	char code1 [CODE_SIZE];
	char code2 [CODE_SIZE];

	puts("remove round trip");
	scanf("%s %s", code1, code2);
	flight fl = codes_to_flight(code1, code2);

	if (remove_round_trip(fl) == ERROR)
		printf("*Impossivel remover voo RT %s %s\n", code1, code2 );
}

void command_N()
{ /* prints out the number of flights 
	from 1 to another airport*/
	char code1 [CODE_SIZE];
	char code2 [CODE_SIZE];
	int count;

	puts("number of flights");
	scanf("%s %s", code1, code2);
	
	int index1 = code_to_index(code1);
	int index2 = code_to_index(code2);

	if (index1 != ERROR && index2 != ERROR)
	{
		count = flight_count(create_flight(index1, index2));
		printf("%d\n", count);
	}

	else if (index1 == ERROR)
		printf("Aeroporto %s inexistente\n",code1);

	else if (index2 == ERROR)
		printf("Aeroporto %s indexcistente\n", code2);
}

void command_P()
{ /* prints out the airport with most flights */
	
	puts("airport with most flights");
	
	int index = most_flights();
	
	printf("%s:%d:%d", 
			airports[index].code,
			airport_flight_count_out(index),
			airport_flight_count_in(index));	
}

void command_Q()
{ /* prints out the airport with most connections */
	int index;
	puts("airport with most connections");
	
	index = most_connections();
	
	printf("%s:%d", 
			airports[index].code,
			airport_connection_count(index));
}

void command_V()
{ /* prints out the most popular flight */
	flight trip; 
	int count;

	puts("most popular flight");
	trip = most_popular_flight();
	count = flight_count(trip);
	printf("%s:%s:%d", 
			airports[trip.out].code,
			airports[trip.in].code,
			count);
}

void command_C()
{ /* closes an airport */
	char code[CODE_SIZE];
	int index;

	puts("close airport");
	scanf("%s", code);
	
	index = code_to_index(code);
	if (close_airport(index) == ERROR)
		printf("*Aeroporto %s inexistente\n", code);	
}

void command_O()
{ /* opens an airport */
	char code [CODE_SIZE];
	int index;
	puts("open airport");
	scanf("%s", code);
	
	index = code_to_index(code);
	if (open_airport(index) == ERROR)
		printf("*Aeroporto %s indexistente\n", code);	
}

void command_L()
{ /* prints lists in differente ways */
	int inst;

	puts("print list");
	scanf(" %d", &inst);
	
	if (inst == 0)
		print_index_order();
	
	else if (inst == 1)
		print_alphabetical_order();
	
	else if (inst == 2)
		print_histogram();
}


int menu()
{	
	char c;

	while (1)
	{ 
		switch (c = getchar())
		{
			case 'A':
				command_A();	
				break;
				
			case 'I':
				command_I();
				break;
				
			case 'F':
				command_F();
				break;
				
			case 'G':
				command_G();
				break;
				
			case 'R':
				command_R();
				break;
				
			case 'S':
				command_S();
				break;
				
			case 'N':
				command_N();
				break;
				
			case 'P':
				command_P();
				break;
				
			case 'Q':
				command_Q();
				break;
			
			case 'V':
				command_V();
				break;
				
			case 'C':
				command_C();
				break;
				
			case 'O':
				command_O();
				break;
				
			case 'L':
				command_L();
				break;
				
			case 'X':
				puts("exit program");
				printf("%d:%d", total_flight_count, nr_of_airports);
				return 0;
				break;
			
			case 'W':
				printf("( ͡° ͜ʖ ͡°)\n");
				break;

			default:
				printf("commando nao reconhecido\n");
		}
		getchar();
	}
}

int main()
{
	int i,j;
	for (i = 0; i < MAX_AIRPORTS; i++)
	{	
		for (j = 0; j < MAX_AIRPORTS; j++)
			airSpace[i][j] = 0;
		airports[i].index = ERROR;
	}
	menu();
	return 0;
}

