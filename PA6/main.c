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

	//Initialize structs
	Carrier carrier1 = {
		.position = {{0,0},{0,0},{0,0},{0,0},{0,0}},
		.hits = 0
	};
	Battleship battleship1 = {
	.position = {{0,0},{0,0},{0,0},{0,0}},
	.hits = 0
	};
	Cruiser cruiser1 = {
	.position = {{0,0},{0,0},{0,0}},
	.hits = 0
	};
	Submarine sub1 = {
	.position = {{0,0},{0,0},{0,0}},
	.hits = 0
	};
	Destroyer destroyer1 = {
	.position = {{0,0},{0,0}},
	.hits = 0
	};
	Carrier carrier2 = {
	.position = {{0,0},{0,0},{0,0},{0,0},{0,0}},
	.hits = 0
	};
	Battleship battleship2 = {
	.position = {{0,0},{0,0},{0,0},{0,0}},
	.hits = 0
	};
	Cruiser cruiser2 = {
	.position = {{0,0},{0,0},{0,0}},
	.hits = 0
	};
	Submarine sub2 = {
	.position = {{0,0},{0,0},{0,0}},
	.hits = 0
	};
	Destroyer destroyer2 = {
	.position = {{0,0},{0,0}},
	.hits = 0
	};

	//Initialize arrays
	initialize_board(player_board, MAX_ROWS, MAX_COL);
	initialize_board(pc_board, MAX_ROWS, MAX_COL);

	display_menu();
	ship_placement = choose_ship_placement();
	if (ship_placement == 1) {
		ship_placement_manual(player_board);
	}
	else if (ship_placement == 2) {
		ship_placement_auto();
		display_boards(player_board, pc_board);
	}
	//display_boards(player_board, pc_board);

	return 0;
}