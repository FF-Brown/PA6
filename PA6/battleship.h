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
#define CARRIER 5
#define BATTLESHIP 4
#define CRUISER 3
#define SUBMARINE 3
#define DESTROYER 2
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct coordinate {
	int x;
	int y;
}Coordinate;
typedef struct stats {
	int hits;
	int misses;
	int shots;
	double ratio;
}Stats;

void display_menu(void);
void rules(void);
void initialize_board(char player_board[][MAX_COL], int rows, int columns);
void display_boards(char player_board[][MAX_COL], char pc_board[][MAX_COL]);
int choose_ship_placement(void);
bool check_space(char player_board[][MAX_COL], Coordinate location);
void ship_placement_manual(char player_board[][MAX_COL]);
void ship_placement_auto(char player_board[][MAX_COL]);
bool ship_spacer(char player_board[][MAX_COL], Coordinate starting_point, char direction, int length);
void display_player_board(char player_board[][MAX_COL]);
void display_pc_board(char pc_board[][MAX_COL]);
int direction_gen(void);
Coordinate rand_shot(void);
