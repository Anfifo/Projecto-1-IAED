#include <stdio.h>

#define MAX_AIRPORTS 1000
#define MAX_FLIGHTS_PER_AIRPORT 1000
#define CODE_SIZE 3
#define SMALLER -1
#define GREATER 0
#define EQUAL 1


/*  == == == == == == == ==
	= Types and variables =
	== == == == == == == ==*/
typedef struct
{
	char code [10];
	int capacity; /*has to be > 0*/
	int state; //on - 1; off - 2//
	int index;
}airport;


typedef struct 
{
	int out;
	int in;

}flight;


/* global variables */
airport airports[MAX_AIRPORTS];
int airpMatrix[MAX_AIRPORTS][MAX_AIRPORTS];
int next_airport_index = 0;
int all_flights = 0;




/*  == == == == == == == == ==
	=   Auxiliar Functions   =
	== == == == == == == == ==*/

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
		if (code1[i] < code2[i])
			return SMALLER;
			
		else if (code1[i] > code2[i])
			return GREATER;
	}
	return EQUAL;

}


int code_to_index(char code[])
{
	int i;
	int character;
	
	for (i = 0; i < next_airport_index; i++)
	{
		if ((character = compare_codes(airports[i].code, code)) == 1)
			return airports[i].index;	
	}
	return -1;
}




/*  == == == == == == == ==
	=    Type Functions   =
	== == == == == == == == */

void create_airport(char code[], int capa)
{
	int index = next_airport_index;
	copy_codes(airports[index].code, code);

	airports[index].capacity = capa;  
	airports[index].index = index;
	next_airport_index++;
}


void modify_capacity(char code[], int new_capa)
{
	int index = code_to_index(code);
	
	airports[index].capacity = new_capa;
}

void add_round_trip(char code1[], char code2[])
{
	int index1 = code_to_index(code1);
	int index2 = code_to_index(code2);
	
	airpMatrix[index1][index2]++;
	airpMatrix[index2][index1]++;
	
	all_flights += 2;
}

void remove_round_trip(char code1[], char code2[])
{
	int index1 = code_to_index(code1);
	int index2 = code_to_index(code2);
	
	airpMatrix[index1][index2]--;
	airpMatrix[index2][index1]--;
	
	all_flights -= 2;
}

void add_flight(char code1[], char code2[])
{
	int index1 = code_to_index(code1);
	int index2 = code_to_index(code2);
	
	airpMatrix[index1][index2]++;
	
	all_flights++;
}

void remove_flight(char code1[], char code2[])
{
	int index1 = code_to_index(code1);
	int index2 = code_to_index(code2);
	
	airpMatrix[index1][index2]--;
	
	all_flights--;
}

int flight_count(int index1, int index2)
{
	
	return airpMatrix[index1][index2];
	
}

int airport_flight_count_out(int index)
{
	int count = 0;
	int i;
	
	for(i = 0; i < next_airport_index; i++)
	
		count += airpMatrix[index][i];	
	
	return count;
}

int airport_flight_count_in(int index)
{
	int count = 0;
	int i;
	
	for(i = 0; i < next_airport_index; i++)
	
		count += airpMatrix[i][index];	
	
	return count;
}


int airport_connection_count(int index)
{
	int count = 0;
	int i;
	
	for (i = 0; i < next_airport_index; i++)
	{
		if (airpMatrix[index][i] > 0 || airpMatrix[i][index] > 0)
			count++;
	}
	
	return count;
}

int most_flights()
{
	int index;
	int count = 0;
	int max = 0;
	int max_index = 0;
	
	for(index = 0; index < next_airport_index; index++)
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
{
	int index;
	int count = 0;
	int max = 0;
	int max_index = 0;
	
	for(index = 0; index < next_airport_index; index++)
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
{
	int out = 0;
	int in = 0;
	int max = 0;
	flight max_flight;
	
	for (out = 0; out < next_airport_index; out++)
	{
		for (in = 0; in < next_airport_index; in++)
		{
			if (airpMatrix[out][in] > max)
			{		
				max = flight_count(out, in);
				max_flight.out = out;
				max_flight.in = in;
			}	
		}
	}
	return max_flight;
}

void close_airport(char code[])
{
	int index = code_to_index(code);
	int i;
	
	for (i = 0; i < next_airport_index; i++)
	{
		airpMatrix[index][i]=0;
		airpMatrix[i][index]=0;
	}
	
	airports[index].state = 0;
}

void open_airport(char code[])
{
	int index = code_to_index(code);
	
	airports[index].state = 0;
}

void print_index_order()
{
	int i;
	int out;
	int in;
	
	for (i = 0; i < next_airport_index; i++)
	{
		out = airport_flight_count_out(i);
		in = airport_flight_count_in(i);
		
		printf("%s:%d:%d:%d\n", 
				airports[i].code, 
				airports[i].capacity, 
				out, 
				in);
	}
}

void sort_alphabetical(int array[])
{
	int i, j;
	int value;
	
	for ( i = 0; i < next_airport_index; i++)
	{	
		for ( j = i+1; j < next_airport_index; j++)
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
	int array[next_airport_index];
	
	sort_alphabetical(array);
	
	for (i = 0; i < next_airport_index; i++)
	{
		int out = airport_flight_count_out(array[i]);
		int in = airport_flight_count_in(array[i]);
		
		printf("%s:%d:%d:%d\n", 
				airports[array[i]].code, 
				airports[array[i]].capacity, 
				out, 
				in);
	}
}

void print_histogram()
{
	int i;
	int j;
	int count_out;
	int count_in;
	int array[MAX_FLIGHTS_PER_AIRPORT];
	
	for (i = 0; i < next_airport_index; i++)
	{
		count_out = airport_flight_count_out(airports[i].index);
		count_in = airport_flight_count_in(airports[i].index);
		array[count_in+count_out]++;
	}
	
	i = 0;
	j = 0;
	
	while (i < next_airport_index) /*born to be while*/
	{
		if (array[j] != 0)
		{
			printf("%d:%d\n", j, array[j]);
			i++;
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
	create_airport(code, capa);
}

void command_I()
{ /* changes an airport's capacity*/
	char code [CODE_SIZE];
	int new_capa;

	puts("modify airport capacity");
	scanf("%s %d", code, &new_capa);
	modify_capacity(code, new_capa);
}

void command_F()
{ /* adds a roundtrip flight */
	char code1 [CODE_SIZE];
	char code2 [CODE_SIZE];

	puts("add round trip");
	scanf("%s %s", code1, code2);
	add_round_trip(code1, code2);
}

void command_G()
{ /* adds a single flight */ 
	char code1 [CODE_SIZE];
	char code2 [CODE_SIZE];

	puts("add flight");
	scanf("%s %s", code1, code2);
	add_flight(code1, code2);
}

void command_R()
{ /*removes a flights */
	char code1 [CODE_SIZE];
	char code2 [CODE_SIZE];

	puts("remove flight");
	scanf("%s %s", code1, code2);
	remove_flight(code1, code2);
}

void command_S()
{ /* removes a roundtrip flights */
	char code1 [CODE_SIZE];
	char code2 [CODE_SIZE];

	puts("remove round trip");
	scanf("%s %s", code1, code2);
	remove_round_trip(code1, code2);
}

void command_N()
{ /* prints out the number of flights 
	from 1 to another airport*/
	char code1 [CODE_SIZE];
	char code2 [CODE_SIZE];
	int index1, index2, count;

	puts("number of flights");
	scanf("%s %s", code1, code2);
	
	index1 = code_to_index(code1);
	index2 = code_to_index(code2);
	
	count = flight_count(index1, index2);
	printf("%d\n", count);
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
	count = flight_count(trip.out, trip.in);
	printf("%s:%s:%d", 
			airports[trip.out].code,
			airports[trip.in].code,
			count);
}

void command_C()
{ /* closes an airport */
	char code[CODE_SIZE];

	puts("close airport");
	scanf("%s", code);
	close_airport(code);	
}

void command_O()
{ /* opens an airport */
	char code [CODE_SIZE];

	puts("open airport");
	scanf("%s", code);
	open_airport(code);	
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
		switch (c = getchar() )
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
				printf("%d:%d", all_flights, next_airport_index);
				return 0;
				break;
		}
		getchar();
	}
}

int main()
{
	menu();
	return 0;
}

