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

#include "main.h"


void command_A()
{ /* adds an airport to airSpace */
	char IDcode [CODE_SIZE];
	int capacity;
	scanf("%s %d", IDcode, &capacity);

	add_airport(IDcode, capacity);
}

void command_I()
{ /* changes an airport's capacity */
	char IDcode [CODE_SIZE];
	int capacity_change;
	scanf("%s %d", IDcode, &capacity_change);
	int index = IDcode_to_index(IDcode);

	if ( modify_capacity(index, capacity_change) == ERROR)
		printf("*Capacidade de %s inalterada\n",IDcode);		
}

void command_F()
{ /* adds roundtrip flights */
	char IDcode1 [CODE_SIZE];
	char IDcode2 [CODE_SIZE];
	scanf("%s %s", IDcode1, IDcode2);
	flight fl = IDcodes_to_flight(IDcode1,IDcode2);
	
	if (add_round_trip(fl) == ERROR)
		printf("*Impossivel adicionar voo RT %s %s\n", IDcode1, IDcode2);
}

void command_G()
{ /* adds a single flight */ 
	char IDcode1 [CODE_SIZE];
	char IDcode2 [CODE_SIZE];
	scanf("%s %s", IDcode1, IDcode2);
	flight fl = IDcodes_to_flight(IDcode1, IDcode2);

	if (add_flight(fl) == ERROR)
		printf("*Impossivel adicionar voo %s %s\n", IDcode1, IDcode2);
}

void command_R()
{ /* removes a single flight */
	char IDcode1 [CODE_SIZE];
	char IDcode2 [CODE_SIZE];
	scanf("%s %s", IDcode1, IDcode2);
	flight fl = IDcodes_to_flight(IDcode1, IDcode2);

	if (remove_flight(fl) == ERROR)
		printf("*Impossivel remover voo %s %s\n", IDcode1, IDcode2);
}

void command_S()
{ /* removes roundtrip flights */
	char IDcode1 [CODE_SIZE];
	char IDcode2 [CODE_SIZE];
	scanf("%s %s", IDcode1, IDcode2);
	flight fl = IDcodes_to_flight(IDcode1, IDcode2);

	if (remove_round_trip(fl) == ERROR)
		printf("*Impossivel remover voo RT %s %s\n", IDcode1, IDcode2 );
}

void command_N()
{ /* prints out the number of flights 
	 from one airport to another */
	char IDcode1 [CODE_SIZE];
	char IDcode2 [CODE_SIZE];
	int count1,count2;
	scanf("%s %s", IDcode1, IDcode2);
	int index1;
	int index2;

	if ((index1 = IDcode_to_index(IDcode1)) == ERROR)
		printf("Aeroporto %s inexistente\n",IDcode1);

	if ((index2 = IDcode_to_index(IDcode2)) == ERROR)
		printf("Aeroporto %s inexistente\n", IDcode2);

	if (index1 != ERROR && index2 != ERROR)
	{
		count1 = flight_count(create_flight(index1, index2));
		count2 = flight_count(create_flight(index2, index1));
		printf("Voos entre cidades %s:%s:%d:%d\n",
				IDcode1, IDcode2, count1, count2);
	}
}

void command_P()
{ /* prints the airport with most flights */
	int index = most_flights();
	
	printf("Aeroporto com mais rotas %s:%d:%d\n", 
			airports[index].IDcode,
			airport_flight_count_out(index),
			airport_flight_count_in(index));	
}

void command_Q()
{ /* prints the airport with most connections */
	int index = most_connections();
	
	printf("Aeroporto com mais ligacoes %s:%d\n", 
			airports[index].IDcode,
			airport_connection_count(index));
}

void command_V()
{ /* prints out the most popular flight */
	flight fl; 
	int count;

	fl = most_popular_flight();
	count = flight_count(fl);
	printf("Voo mais popular %s:%s:%d\n", 
			airports[fl.out].IDcode,
			airports[fl.in].IDcode,
			count);
}

void command_C()
{ /* closes an airport */
	char IDcode[CODE_SIZE];
	int index;
	scanf("%s", IDcode);
	index = IDcode_to_index(IDcode);
	
	if (close_airport(index) == ERROR)
		printf("*Aeroporto %s inexistente\n", IDcode);	
}


void command_O()
{ /* opens an airport */
	char IDcode [CODE_SIZE];
	int index;
	scanf("%s", IDcode);
	index = IDcode_to_index(IDcode);
	
	if (open_airport(index) == ERROR)
		printf("*Aeroporto %s indexistente\n", IDcode);	
}


void command_L()
{ /*prints lists in a way that 
	depends on scanned input */
	int inst;
	scanf(" %d", &inst);
	switch(inst)
	{
		case 0:
			print_index_order();
			break;

		case 1:
			print_alphabetical_order();
			break;

		case 2:
			print_histogram();
			break;
	}
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
				/* exits program */
				printf("%d:%d\n", 
					total_flight_count,
					nr_of_airports);
				return;

			default:
				break;
				/* to consume '\n' and any other unintended character */
		}
	}
}


int main()
{
	initialize_airSpace();
	menu();
	return 0;
}
