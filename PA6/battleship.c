/*
	Author: Nathan Brown
	Created: 10/25/2019
	Description: The classic game of Battleship in text-based format versus a computer. Player is allowed to choose manual or random placement of ships, and difficulty of computer player. A log file is created detailing gameplay.
*/

#include "battleship.h"

/*
	Function: display_menu()
	Date Created: 10/26/2019
	Description: Allows user to choose between displaying rules, playing the game, and exiting. New and improved version with a do-while loop.
	Preconditions: None
	Postconditions: Loops back into menu if rules chosen. Breaks loop if --> game. Ends program if exit.
*/
void display_menu(void)
{
	int option = 0;

	//Display menu until receiving valid input
	
	do{
		printf("\n~~~~~~ MAIN MENU ~~~~~~\n\n");
		printf("1. Rules\n");
		printf("2. Play Game\n");
		printf("3. Exit\n");
		printf("Select an option by typing in a number.\n");
		scanf("%d", &option);

		//Run process based on input
		switch (option) {
		case RULES:
			system("cls");
			rules();
			display_menu();
			break;
			//Leave switch and while loop to begin playing game
		case PLAY:
			system("cls");
			printf("Good luck!\n\n");
			break;
			//Exit program
		case EXIT:
			printf("See you next time!\n");
			exit(0);
			break;
		default:
			break;
		}
		if (option < 1 || option > 3)
			printf("Invalid entry.\n");
	} while (option < 1 || option > 3);
}
/*
	Function: rules()
	Date Created: 10/26/2019
	Description: Displays rules of battleship
	Preconditions: Menu displayed
	Postconditions: Rules displayed
*/
void rules(void)
{
	printf("Battleship is a two-player game. It is mostly dependent on chance, with some strategy involved.\n");
	printf("Both players have a 10x10 grid on which to place their 5 ships. The ships can be placed anywhere so long as they do not overlap or go outside the 10x10 area. Once the game has begun, the ships' positions do not change.\n\n");
	printf("Players do not know where each other's ships are, and take turns calling out coordinates for missile strikes. The other player reports whether or not a ship was hit (but not which ship was hit). Traditionally a second grid is provided to record your own hits/misses. In this version, the record is created automatically.\n");
	printf("When all the coordinates corresponding to one ship have been hit, the owner of the ship must tell their opponent that they have sunk a ship.\n");
	printf("The game ends when all ships belonging to one player have been sunk.\n");
}
void initialize_board(char player_board[][MAX_COL], int rows, int columns)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			player_board[i][j] = '~';
		}
	}
}
void display_board(char player_board[][MAX_COL], char pc_board[][MAX_COL])
{
	int current_element = 0;
	int i = 0;
	printf("   0 1 2 3 4 5 6 7 8 9 \n");
	for (i = 0; i < MAX_ROWS; i++) {
		printf(" %d ", i);
		for (int j = 0; j < MAX_COL; j++) {
			printf("%c ", player_board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	printf("   0 1 2 3 4 5 6 7 8 9 \n");
	for (i = 0; i < MAX_ROWS; i++) {
		printf(" %d ", i);
		for (int j = 0; j < MAX_COL; j++) {
			if (pc_board[i][j] == 'x' || pc_board[i][j] == 'o' || pc_board[i][j] == '~')
				printf("%c ", pc_board[i][j]);
			else
				printf("~ ");
		}
		printf("\n");
	}

}
/*
	Function: chooose_ship_placement()
	Date Created: 10/26/2019
	Description: Allows the player to decide whether to manually place ships or have their positions chosen at random
	Preconditions: Player has chosen to begin the game
	Postconditions: Returns 1 or 2 for manual or auto ship placement respectively
*/
int choose_ship_placement(void)
{
	int option = 0;
	do {
		printf("You may either place your ships manually or have them placed at random. Which would you prefer?\n");
		printf("1. Manual Placement\n");
		printf("2. Automatic Placement\n");
		scanf("%d", &option);
		if (option < 1 || option > 2)
			printf("Invalid input.\n");
	} while (option < 1 || option > 2);
	return option;
}
/*
	Function: ship_placement_manual()
	Date Created: 10/26/2019
	Description: Allows user to input coordinates for each ship. Saves coordinates in struct arrays.
	Preconditions: choose_ship_placement() called
	Postconditions: Ships placed on board
*/
void ship_placement_manual()
{
	printf("You may now choose where you would like to place your ships.\n");
	//display_board()
	//printf("")
}
/*
	Function: ship_placement_auto()
	Date Created: 10/26/2019
	Description: Allows for random placement of ships. Proposed functionality: Generates coordinate pair and checks if available. This is starting point for ship. Generates new coordinate pair. X value is horizontal/vertical (value of -1 or 1). Y value is direction of plotting (1 or -1). If x is -1 (for example), adds y value to x coordinate of starting point. If x is 1, instead adds quantum number y (q_y) to y value of starting point (SP). Checks if that space is available. If not, toggle q_y (multiply by -1) and check again. If available, adds coordinate there and uses as new evaluation point (EP). If space check fails after q_y toggle, then toggle q_x. Check, toggle q_y if necessary. After 4 total failures, generate new SP. If 2+ spaces have been filled (including SP) and checks fail, try building from SP with toggled q_y.

		May get simplified to just find a new SP if any of its coordinates fail to be placed

	Preconditions: Player chooses auto placement OR computer is placing ships. Also a high tolerance for complicated-ass logic.
	Postconditions: Ships placed on board
*/
void ship_placement_auto()
{
	printf("Your ships have been placed at random and now occupy the following spaces:\n");
}