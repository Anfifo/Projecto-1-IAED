
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
	int out;
	int in;

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
}

void add_flight(char code1[], char code2[])
{
	int index1 = code_to_index(code1);
	int index2 = code_to_index(code2);
	
	airpMatrix[index1][index2]++;
}

void remove_flight(char code1[], char code2[]);
{
	int index1 = code_to_index(code1);
	int index2 = code_to_index(code2);
	
	airpMatrix[index1][index2]--;
}

void remove_round_trip(char code1[], char code2[])
{
	int index1 = code_to_index(code1);
	int index2 = code_to_index(code2);
	
	airpMatrix[index1][index2]--;
	airpMatrix[index2][index1]--;
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
	flight max_flight = 0;
	
	for (out = 0; out < next_airport_index; out++)
	{
		for (in = 0; in < next_airport_index; in++)
		{
			if (airports[out][in] > max)
			{		
				max = flight_count[out][in];
				max_flight.out = out;
				max_flight.in = in;
			}	
		}
	}
	return max_flight;
}

void close_airport(char code[])
{
	int code_to_index(code);
	
	



	




void menu()
{
	int count = 0;
	int index = 0;
	int index1 = 0;
	int index2 = 0;
	char code1[CODE_SIZE];
	char code2[CODE_SIZE];
	flight trip;
	
	while (1)
	{
		switch (c = getchar() )
		{
			case 'A':
			
				puts("add airport");
				scanf("%s %d", code, &capa);
				create_airport(code, capa);
			
				break;
				
			case 'I':
			
				puts("modify airport capacity");
				scanf("%s %d", code, new_capa);
				modify_capacity(code, new_capa);
			
				break;
				
			case 'F':
			
				puts("add round trip");
				scanf("%s %s", code1, code2);
				add_round_trip(code1, code2);
				
				break;
				
			case 'G':
			
				puts("add flight");
				scanf("%s %s", code1, code2);
				add_flight(code1, code2);
				
				break;
				
			case 'R':
			
				puts("remove flight");
				scanf("%s %s", code1, code2);
				remove_flight(code1, code2);
				
				break;
				
			case 'S':
			
				puts("remove round trip");
				scanf("%s %s", code1, code2);
				remove_round_trip(code1, code2);
			
				break;
				
			case 'N':
				
				puts("number of flights");
				scanf("%s %s" code1, code2);
				
				index1 = code_to_index(code1);
				index2 = code_to_index(code2);
				
				count = flight_count(index1, index2);
				printf("%d\n", count);
			
				break;
				
			case 'P':
			
				puts("airport with most flights");
				
				index = most_flights();
				
				printf("%s:%d:%d", 
						airports[index].code,
						airport_flight_count_out(index),
						airport_flight_count_in(index));
			
				break;
				
			case 'Q':
			
				puts("airport with most connections");
				
				index = most_connections();
				
				printf("%s:%d", 
						airports[index].code,
						airport_connection_count(index));
								
				break;
			
			case 'V':
			
				puts("most popular flight");
				trip = most_popular_flight();
				count = flight_count(trip.out, trip.in);
				printf("%s:%s:%d", 
						airports[trip.out].code,
						airports[trip.in].code,
						count);
				
				break;
				
			case 'C':
			
				puts("close airport");
				
				
			
				break;
				
			case 'O':
				puts("open airport");
				
				break;
				
			case 'L':
				puts("print list");
				
				break;
				
			case 'X':
				puts("exit program");
				
				break;

main()
{
	return 0;
}
