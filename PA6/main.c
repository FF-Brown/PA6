/*
	Author: Nathan Brown
	Created: 10/25/2019
	Description: The classic game of Battleship in text-based format versus a computer. Player is allowed to choose manual or random placement of ships, and difficulty of computer player. A log file is created detailing gameplay.
*/

#include "battleship.h"

int main(void) {

	//Declare variables, seed rand()
	srand(time(NULL));
	int ship_placement = 0;
	char player_board[MAX_ROWS][MAX_COL] = { 0 };
	char pc_board[MAX_ROWS][MAX_COL] = { 0 };
	int ship_health[2][5] = { 0 };

	//Initialize structs
	Stats stats1 = { 0 };
	Stats stats2 = { 0 };

	//Initialize arrays
	initialize_board(player_board, MAX_ROWS, MAX_COL);
	initialize_board(pc_board, MAX_ROWS, MAX_COL);

	//Menu
	display_menu();

	//Let player set ships
	ship_placement = choose_ship_placement();
	if (ship_placement == 1)
		ship_placement_manual(player_board);
	else if (ship_placement == 2) {
		ship_placement_auto(player_board);
		display_player_board(player_board);
	}

	//Set ships for PC
	printf("Placing opponent's ships...\n");
	ship_placement_auto(pc_board);

	return 0;
}