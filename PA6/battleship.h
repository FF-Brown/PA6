/*
	Author: Nathan Brown
	Created: 10/25/2019
	Description: The classic game of Battleship in text-based format versus a computer. Player is allowed to choose manual or random placement of ships, and difficulty of computer player. A log file is created detailing gameplay.
*/

#define _CRT_SECURE_NO_WARNINGS
#define RULES 1
#define PLAY 2
#define EXIT 3
#define MAX_ROWS 10
#define MAX_COL 10

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//typedef struct coordinate {
//	int x;
//	int y;
//}Coordinate;

void display_menu(void);
void rules(void);
void initialize_board(char player_board[][MAX_COL], int rows, int columns);
void display_board(char player_board);
int choose_ship_placement(void);
void ship_placement_manual();
void ship_placement_auto();
