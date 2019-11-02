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
	int ship_health[2][5] = { 
		{ 5, 4, 3, 3, 2},
		{ 5, 4, 3, 3, 2}
	};
	int turn = 0, current_player = 0;
	Coordinate target = { 0, 0 };
	Stats stats1 = { 0 };
	Stats stats2 = { 0 };
	char result = '\0';
	bool available = false;

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
		system("cls");
		display_player_board(player_board);
		system("pause");
	}

	//Set ships for PC
	printf("Placing opponent's ships...\n");
	system("pause");
	ship_placement_auto(pc_board);
	system("cls");
	display_pc_board(pc_board);

	//Determine first player
	turn = turn_order();
	current_player = get_current_player(turn);
	printf("Player %d will go first.\n", current_player);

	//Player turn
	targeting_sequence(pc_board, ship_health, current_player);
	//PC turn
	targeting_sequence(player_board, ship_health, current_player);

	return 0;
}