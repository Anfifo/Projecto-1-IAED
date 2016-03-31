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
 * assumes there won't ever be 2 airports with same ID
 * :: input: char [], int -- airport's IDcode, airport's capacity ( > 0)
 */
void command_I();
/* 
 * calls functions to add/subtract to the existing airport's capacity the int 'change'
 * prints an error if there was no change to the capacity 
 * :: input: char [], int -- airport's IDcode, change to capacity (positive or negative)
 */
void command_F();
/*
 * calls functions to add a round_trip flight between 2 input airports
 * prints an error if one or both airports were undefined or it was impossible to add flight
 * assumes the IDcodes are different
 * :: input: char [], char [] -- airport 1 IDcode, airport 2 IDcode
 */
void command_G();
/*
 * calls functions to to add a flight from input's airport 1 to airport 2
 * prints an error if it wasn't possible to add the flight
 * assumes the IDcodes are different
 * :: input: char [], char[] -- airport 1 IDcode, airport 2 IDcode
 */
void command_R();
/*
 * calls functions to remove a flight from input's airport 1 to airport 2 
 * prints error it wasn't possible to remove flight
 * assumes the IDcodes are different
 * :: input: char [], char [] -- airport 1 IDcode, airport 2 IDcode
 */
void command_S();
/*
 * calls functions to remove a round trip flight between input's airport 1 to airport 2 
 * prints error it wasn't possible to remove flight
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
 * prints airport's ID: Number of flights outgoing : number of flight incoming 
 * :: input: --
 */
void command_Q();
/*
 * calls functions to calculate the airport with most connection to other airports
 * prints the aiport 
 * :: input --
 */
void command_V();
/*
 * calls functions to calculate and prints the most popular flight 
 * prints the ID of outgoing airport and incoming airport and the count
 * :: input:
 */
void command_C();
/*
 * closes given airport by input and removes all flights from and to this airport
 * prints error if airport is not defined 
 * :: input: char[] -- airport's IDcode
 */
void command_L();
/*
 * prints a list in function of the instruction
 * 0: index order -- 1: alphabetical -- 2: histogram
 * :: input: int -- 0 <= instruction <= 2
 */
void menu();
/*
 * calls a command to executed based on the character received from input
 * shutdowns program if character = 'X'
 * ignores unknown commands
 * :: input: char -- known commands: A, I, F, G, R, S, N , P, Q, V, C, O, L, X
 */
