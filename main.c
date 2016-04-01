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
#include "commands.h"


void menu();
/*
 * executes a command based on the character received from input
 * shutdowns program if character = 'X'
 * ignores unknown commands
 * :: input: char -- known commands: A, I, F, G, R, S, N , P, Q, V, C, O, L, X
 */


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
