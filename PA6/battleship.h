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

/*
	Struct: Coordinate
	int x
	int y
*/
typedef struct coordinate {
	int x;
	int y;
}Coordinate;
/*
	Struct: Stats
	int hits
	int misses
	int shots
	double ratio
*/
typedef struct stats {
	int hits;
	int misses;
	int shots;
	double ratio;
}Stats;

/*
	Function: display_menu()
	Date Created: 10/26/2019
	Description: Allows user to choose between displaying rules, playing the game, and exiting. New and improved version with a do-while loop.
	Preconditions: None
	Postconditions: Loops back into menu if rules chosen. Breaks loop if --> game. Ends program if exit.
*/
void display_menu(void);
/*
	Function: rules()
	Date Created: 10/26/2019
	Description: Displays rules of battleship
	Preconditions: Menu displayed
	Postconditions: Rules displayed
*/
void rules(void);
/*
	Function: initialize_board()
	Date Created: 10/27/2019
	Description: Sets all elements of one board to ~
	Preconditions: None
	Postconditions: Board initialized properly
*/
void initialize_board(char player_board[][MAX_COL], int rows, int columns);
/*
	Function: display_boards()
	Date Created: 10/27/2019
	Description: Displays both player and computer boards. Does not display computer ships (that would be cheating lol)
	Preconditions: None
	Postconditions: Boards displayed for further use
*/
void display_boards(char player_board[][MAX_COL], char pc_board[][MAX_COL]);
/*
	Function: chooose_ship_placement()
	Date Created: 10/26/2019
	Description: Allows the player to decide whether to manually place ships or have their positions chosen at random
	Preconditions: Player has chosen to begin the game
	Postconditions: Returns 1 or 2 for manual or auto ship placement respectively
*/
int choose_ship_placement(void);
/*
	Function: check_space()
	Date Created: 10/27/2019
	Description: Takes a board and a coordinate. Checks whether the board is empty (~) in that space.
	Preconditions: Boards initialized
	Postconditions: T/F returned, message on screen if error
*/
bool check_space(char player_board[][MAX_COL], Coordinate location);
/*
	Function: ship_placement_manual()
	Date Created: 10/26/2019
	Description: Allows user to input coordinates for each ship. Saves coordinates in struct arrays.
	Preconditions: choose_ship_placement() called
	Postconditions: Ships placed on board
*/
void ship_placement_manual(char player_board[][MAX_COL]);
/*
	Function: ship_placement_auto()
	Date Created: 10/26/2019
	Description: GREATLY SIMPLIFIED VERSION: Structure resembling that of ship_placement_manual(). Generates random starting values, checks to see if there's space to place ship. If not, tries again. If so, places ship. Loops for all 5 ships, adjusting ship length and corresponding letter each iteration. Reports successful when it reaches the end.
	Preconditions: Player chooses auto placement OR computer is placing ships. Also a high tolerance for complicated-ass logic.
	Postconditions: Ships placed on board
*/
void ship_placement_auto(char player_board[][MAX_COL]);
/*
	Function: ship_spacer()
	Date Created: 10/27/2019
	Description: Checks to see if there is enough space in a row/column to place a ship based on starting coordinate, direction, and length
	Preconditions: Starting coordinate for ship chosen as well as direction, length determined
	Postconditions: T/F returned
*/
bool ship_spacer(char player_board[][MAX_COL], Coordinate starting_point, char direction, int length);
/*
	Function: display_player_board()
	Date Created: 10/27/2019
	Description: Displays only the player's board
	Preconditions: Boards initialized
	Postconditions: Board displayed
*/
void display_player_board(char player_board[][MAX_COL]);
/*
	Function: display_pc_board()
	Date Created: 10/27/2019
	Description: Displays only the computer's board
	Preconditions: Boards initialized
	Postconditions: Board displayed
*/
void display_pc_board(char pc_board[][MAX_COL]);
/*
	Function: quantum_numbers()
	Date Created: 10/27/2019
	Description: Generates a coordinate pair with values of either 1 or -1 for use in automatic ship placement
	Preconditions: None
	Postconditions: Pair of quantum numbers returned
*/
int direction_gen(void);
Coordinate rand_shot(void);
int turn_order(void);
int get_current_player(int turn);
Coordinate get_target(void);
char target_check(Coordinate target, char board[][MAX_COL]);
void update_ship_health(char enemy_board[][MAX_COL], Coordinate target, int ship_health[][5], int current_player);
void targeting_sequence(char enemy_board[][MAX_COL], int ship_health[][5], int current_player);
