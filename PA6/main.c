/*
	Author: Nathan Brown
	Created: 10/25/2019
	Description: The classic game of Battleship in text-based format versus a computer. Player is allowed to choose manual or random placement of ships, and difficulty of computer player. A log file is created detailing gameplay.
	Note to grader (Katrina): When the pc chooses a target, occasionally (more towards the end of the game) it *looks* like it is selecting multiple targets. This is not the case. It happens when the target generated has already been chosen previously. The pc then chooses a new target. As it does not affect the outcome of the turn, I decided it wasn't worth changing.
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
	Stats stats1 = { 0, 0, 0, 0.0 };
	Stats stats2 = { 0, 0, 0, 0.0 };
	Stats stats_tot[2] = { {0,0,0,0.0},{0,0,0,0.0} };
	char result = '\0';
	bool available = false, has_won = false;

	//Initialize things
	initialize_board(player_board, MAX_ROWS, MAX_COL);
	initialize_board(pc_board, MAX_ROWS, MAX_COL);
	init_logfile();

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

	//Determine first player. More detail in function comment blocks.
	turn = turn_order();
	current_player = get_current_player(turn);
	system("cls");
	printf("Player %d will go first.\n", current_player);

	//Loop for turn sequence
	do{
		current_player = get_current_player(turn);
		if (current_player == 1) { //Player turn
			printf("Player 1 turn.\n");
			system("pause");
			system("cls");
			display_boards(player_board, pc_board);
			targeting_sequence(pc_board, ship_health, current_player, &stats1);
			system("pause");
			system("cls");
		}
		else { //PC turn
			printf("Player 2 turn.\n");
			targeting_sequence(player_board, ship_health, current_player, &stats2);
		}
		has_won = win_condition(current_player, ship_health);
		turn++;
	} while (!has_won);

	//After someone wins
	if (current_player == 1) { //Congratulate player
		printf("Congratulations! You win!!\n");
	}
	else { //Hate on player
		printf("You lose! Sucks to suck!\n");
	}

	//Save data
	log_player_stats(stats1, stats2);
	printf("Data successfully saved to file.\n");

	return 0;
}