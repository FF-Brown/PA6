/*
	Author: Nathan Brown
	Created: 10/25/2019
	Description: The classic game of Battleship in text-based format versus a computer. Player is allowed to choose manual or random placement of ships, and difficulty of computer player. A log file is created detailing gameplay.
*/

#include "battleship.h"

int main(void) {

	//Declare variables, seed rand()
	int ship_placement = 0;
	char player_board[MAX_ROWS][MAX_COL] = { 0 };
	char pc_board[MAX_ROWS][MAX_COL] = { 0 };

	initialize_board(player_board, MAX_ROWS, MAX_COL);
	initialize_board(pc_board, MAX_ROWS, MAX_COL);
	display_menu();
	ship_placement = choose_ship_placement();
	if (ship_placement == 1)
		ship_placement_manual();
	else if (ship_placement == 2)
		ship_placement_auto();
	display_board(player_board);

	return 0;
}