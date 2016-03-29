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

#include "airControl.h"

/*  == == == == == == == ==
	=    Main Functions   =
	== == == == == == == ==  */

void command_A()
{ /* adds an airport to airSpace */
	char code[CODE_SIZE];
	int capa;
	scanf("%s %d", code, &capa);

	add_airport(code, capa);
}

void command_I()
{ /* changes an airport's capacity */
	char code [CODE_SIZE];
	int new_capacity;
	scanf("%s %d", code, &new_capacity);
	int index = code_to_index(code);

	if ( modify_capacity(index, new_capacity) == ERROR)
		printf("*Capacidade de %s inalterada\n",code);
		
}

void command_F()
{ /* adds roundtrip flights */
	char code1 [CODE_SIZE];
	char code2 [CODE_SIZE];
	scanf("%s %s", code1, code2);
	flight fl = codes_to_flight(code1,code2);
	
	if (add_round_trip(fl) == ERROR)
		printf("*Impossivel adicionar voo RT %s %s\n", code1, code2);
}

void command_G()
{ /* adds a single flight */ 
	char code1 [CODE_SIZE];
	char code2 [CODE_SIZE];
	scanf("%s %s", code1, code2);
	flight fl = codes_to_flight(code1, code2);

	if (add_flight(fl) == ERROR)
		printf("*Impossivel adicionar voo %s %s\n", code1, code2);
}

void command_R()
{ /* removes a single flight */
	char code1 [CODE_SIZE];
	char code2 [CODE_SIZE];
	scanf("%s %s", code1, code2);
	flight fl = codes_to_flight(code1, code2);

	if (remove_flight(fl) == ERROR)
		printf("*Impossivel remover voo %s %s\n", code1, code2);
}

void command_S()
{ /* removes roundtrip flights */
	char code1 [CODE_SIZE];
	char code2 [CODE_SIZE];
	scanf("%s %s", code1, code2);
	flight fl = codes_to_flight(code1, code2);

	if (remove_round_trip(fl) == ERROR)
		printf("*Impossivel remover voo RT %s %s\n", code1, code2 );
}

void command_N()
{ /* prints out the number of flights 
	 from one airport to another */
	char code1 [CODE_SIZE];
	char code2 [CODE_SIZE];
	int count1,count2;
	scanf("%s %s", code1, code2);
	int index1 = code_to_index(code1);
	int index2 = code_to_index(code2);

	if (index1 != ERROR && index2 != ERROR)
	{
		count1 = flight_count(create_flight(index1, index2));
		count2 = flight_count(create_flight(index2, index1));
		printf("Voos entre cidades %s:%s:%d:%d\n",
				code1, code2, count1, count2);
	}

	if (index1 == ERROR)
		printf("Aeroporto %s inexistente\n",code1);

	if (index2 == ERROR)
		printf("Aeroporto %s inexistente\n", code2);
}

void command_P()
{ /* prints out the airport with most flights */
	int index = most_flights();
	
	printf("Aeroporto com mais rotas %s:%d:%d\n", 
			airports[index].code,
			airport_flight_count_out(index),
			airport_flight_count_in(index));	
}

void command_Q()
{ /* prints out the airport with most connections */
	int index = most_connections();
	
	printf("Aeroporto com mais ligacoes %s:%d\n", 
			airports[index].code,
			airport_connection_count(index));
}

void command_V()
{ /* prints out the most popular flight */
	flight trip; 
	int count;

	trip = most_popular_flight();
	count = flight_count(trip);
	printf("Voo mais popular %s:%s:%d\n", 
			airports[trip.out].code,
			airports[trip.in].code,
			count);
}

void command_C()
{ /* closes an airport */
	char code[CODE_SIZE];
	int index;
	scanf("%s", code);
	index = code_to_index(code);
	
	if (close_airport(index) == ERROR)
		printf("*Aeroporto %s inexistente\n", code);	
}


void command_O()
{ /* opens an airport */
	char code [CODE_SIZE];
	int index;
	scanf("%s", code);
	index = code_to_index(code);
	
	if (open_airport(index) == ERROR)
		printf("*Aeroporto %s indexistente\n", code);	
}


void command_L()
{ /*prints lists in a way that depends
	on scanned instruction */
	int inst;
	scanf(" %d", &inst);
	
	if (inst == 0)
		print_index_order();
	
	else if (inst == 1)
		print_alphabetical_order();
	
	else if (inst == 2)
		print_histogram();
}


void menu()
{	
	while (1)
	{ 
		switch (getchar())
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
				printf("%d:%d\n", 
					total_flight_count,
					nr_of_airports);
				return;
				break;

			default:
				break;
				/* to consume '\n', also no error to avoid wrong output */
		}
	}
}

int main()
{
	int i,j;
	/* initializes airpace with zero flights
	   and all airports as undefined (ERROR index)*/
	for (i = 0; i < MAX_AIRPORTS; i++)
	{	
		for (j = 0; j < MAX_AIRPORTS; j++)
			airSpace[i][j] = 0;
		airports[i].index = ERROR;
	}

	menu();
	return 0;
}
