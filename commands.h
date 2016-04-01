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
#include "air_control.h"

/* this header contains all
 * functions prototypes on main.c 
 * which receive and respond to inputs*/


void command_A();
/*
 * calls functions to add a new airport to the airSpace with input's info
 * assumes the user won't ever input 2 airports with same ID
 * :: input: char [], int -- airport's IDcode, airport's capacity ( > 0)
 */
void command_I();
/* 
 * calls functions to change the airport's capacity
 * prints error if there was no change detected 
 * :: input: char [], int -- airport's IDcode, 
 * change to capacity (positive or negative)
 */
void command_F();
/*
 * calls functions to add a round trip flight between 2 input airports
 * prints error if it was impossible to add flight
 * assumes the IDcodes are different
 * :: input: char [], char [] -- airport 1 IDcode, airport 2 IDcode
 */
void command_G();
/*
 * calls functions to add a flight from input's airport 1 to airport 2
 * prints error if it was impossible to add flight
 * assumes the IDcodes are different
 * :: input: char [], char[] -- airport 1 IDcode, airport 2 IDcode
 */
void command_R();
/*
 * calls functions to remove a flight from input's airport 1 to airport 2 
 * prints error if it was impossible to remove flight
 * assumes the IDcodes are different
 * :: input: char [], char [] -- airport 1 IDcode, airport 2 IDcode
 */
void command_S();
/*
 * calls functions to remove a round trip flight between 2 input airports 
 * prints error if it was impossible to remove flight
 * assumes the IDcodes are different
 * :: input: char [], char [] -- airport 1 IDcode, airport 2 IDcode
 */
void command_N();
/*
 * prints the number of flights from airport 1 to airport 2 
 * prints an error if one or both airports are undefined
 * assumes the IDcodes are different
 * :: input: char [], char[] -- airport 1 IDcode, airport 2 IDcode
 */
void command_P();
/*
 * calls function to calculate the airport with most flights 
 * prints airport's ID : nr of flights outgoing : nr of flights incoming 
 * :: input: --
 */
void command_Q();
/*
 * calls functions to calculate the airport with most connections
 * prints the airport 
 * :: input --
 */
void command_V();
/*
 * calls functions to calculate the most popular flight 
 * prints the ID of outgoing airport and incoming airport and the count
 * :: input:
 */
void command_C();
/*
 * closes input airport and removes all incoming and outgoing flights
 * prints error if airport is undefined 
 * :: input: char[] -- airport's IDcode
 */
 
 void command_O();
/*
 * opens input airport 
 * prints error if airport is undefined 
 * :: input: char[] -- airport's IDcode
 */
 
void command_L();
/*
 * prints a list in function of the following instructions
 * 0: index order -- 1: alphabetical order -- 2: histogram
 * :: input: int -- 0 <= instruction <= 2
 */
void menu();
/*
 * calls a command execute based on the character received from input
 * shutdowns program if character = 'X'
 * ignores unknown commands
 * :: input: char -- known commands: A, I, F, G, R, S, N , P, Q, V, C, O, L, X
 */
