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
/*
	Function: initialize_board()
	Date Created: 10/27/2019
	Description: Sets all elements of one board to ~
	Preconditions: None
	Postconditions: Board initialized properly
*/
void initialize_board(char player_board[][MAX_COL], int rows, int columns)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			player_board[i][j] = '~';
		}
	}
}
/*
	Function: display_boards()
	Date Created: 10/27/2019
	Description: Displays both player and computer boards. Does not display computer ships (that would be cheating lol)
	Preconditions: None
	Postconditions: Boards displayed for further use
*/
void display_boards(char player_board[][MAX_COL], char pc_board[][MAX_COL])
{
	display_player_board(player_board);
	display_pc_board(pc_board);
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
	Function: check_space()
	Date Created: 10/27/2019
	Description: Takes a board and a coordinate. Checks whether the board is empty (~) in that space. 
	Preconditions: Boards initialized
	Postconditions: T/F returned, message on screen if error
*/
bool check_space(char player_board[][MAX_COL], Coordinate location)
{
	bool available = false;
	//Check that coordinate is within bounds of board
	if (location.x < 0 || location.x > 9) {
		printf("Error: x-coordinate out of range.\n");
		available = false;
	}
	else if (location.y < 0 || location.y > 9) {
		printf("Error: y-coordinate out of range.\n");
		available = false; 
	}
	//Check that space is available (as long as it passes previous test)
	else if (player_board[location.y][location.x] == '~')
		available = true;
	else {
		available = false;
		printf("According to the Pauli Exclusion Principle, two identical fermions cannot occupy the same quantum state. Simply put, two pieces of matter cannot exist in the same place at the same time. That includes boats.\n");
	}
	return available;
}
/*
	Function: ship_placement_manual()
	Date Created: 10/26/2019
	Description: Allows user to input coordinates for each ship. Saves coordinates in struct arrays.
	Preconditions: choose_ship_placement() called
	Postconditions: Ships placed on board
*/
void ship_placement_manual(char player_board[][MAX_COL])
{
	char direction = '\0';
	char names[5][15] = { "carrier", "battleship", "cruiser", "submarine", "destroyer" };
	int length = 0;
	Coordinate starting_point = { 0,0 };
	char escribe = '\0';
	bool available = false;
	bool space = false;
	
	//Take input for each ship individually
	for(int i = 0; i < 5; i++){
		display_player_board(player_board);
		do {
			//Input starting coordinate
			printf("First coordinate for %s: ", names[i]);
			scanf("%d%d", &starting_point.x, &starting_point.y);
			//Check bounds of board (0-9)
			if (starting_point.x < 0 || starting_point.x > 9 || starting_point.y < 0 || starting_point.y > 9) {
				printf("Here be dragons!! You've fallen off the edge of the world. Try again.\n");
			}
			//Check to see if the square is open
			else {
				available = check_space(player_board, starting_point);
			}
		} while (starting_point.x < 0 || starting_point.x > 9 || starting_point.y < 0 || starting_point.y > 9 || !available);
		//Set length of ship and which letter to write on board for that ship
		switch (i){
		case 0:
			length = CARRIER;
			escribe = 'k';
			break;
		case 1:
			length = BATTLESHIP;
			escribe = 'b';
			break;
		case 2:
			length = CRUISER;
			escribe = 'c';
			break;
		case 3:
			length = SUBMARINE;
			escribe = 's';
			break;
		case 4:
			length = DESTROYER;
			escribe = 'd';
			break;
		default:
			break;
		}

		//User chooses which direction to place their boat from the starting point
		do{
			printf("Direction (N/E/S/W): ");
			scanf(" %c", &direction);
			if (direction != 'N' && direction != 'n' && direction != 'E' && direction != 'e' && direction != 'S' && direction != 's' && direction != 'W' && direction != 'w')
				printf("That's not even one of the options, bud.\n");
			else
				space = ship_spacer(player_board, starting_point, direction, length);
			//Loop if invalid input or not enough space
		} while ((direction != 'N' && direction != 'n' && direction != 'E' && direction != 'e' && direction != 'S' && direction != 's' && direction != 'W' && direction != 'w') || !space);
		
		//Builds boat in the direction chosen
		switch (direction)
		{
		case 'n':
		case 'N':
			for (int i = 0; i < length; i++)
				player_board[starting_point.y - i][starting_point.x] = escribe;
			printf("Ship successfully placed.\n");
			break;
		case 'e':
		case 'E':
			for (int i = 0; i < length; i++)
				player_board[starting_point.y][starting_point.x + i] = escribe;
			printf("Ship successfully placed.\n");
			break;
		case 's':
		case 'S':
			for (int i = 0; i < length; i++)
				player_board[starting_point.y + i][starting_point.x] = escribe;
			printf("Ship successfully placed.\n");
			break;
		case 'w':
		case 'W':
			for (int i = 0; i < length; i++)
				player_board[starting_point.y][starting_point.x - i] = escribe;
			printf("Ship successfully placed.\n");
			break;
		default:
			break;
		}
	}
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
/*
	Function: ship_locator()
	Date Created: 10/27/2019
	Description: Iterates through a board to locate ships and place their coordinates in the correct struct
	Preconditions: Ships placed on board
	Postconditions: Structs assigned correct coordinates for ships
*/
void ship_locator(char player_board[][MAX_COL], Carrier carrier1, Battleship battleship1, Cruiser cruiser1, Submarine sub1, Destroyer destroyer1)
{

}
/*
	Function: ship_spacer()
	Date Created: 10/27/2019
	Description: Checks to see if there is enough space in a row/column to place a ship based on starting coordinate, direction, and length
	Preconditions: Starting coordinate for ship chosen as well as direction, length determined
	Postconditions: T/F returned
*/
bool ship_spacer(char player_board[][MAX_COL], Coordinate starting_point, char direction, int length)
{
	bool available = true;
	Coordinate checkpoint = { 0, 0 };

	switch (direction)
	{
	case 'n':
	case 'N':
		for (int i = 0; i < length && available; i++) {
			checkpoint.y = starting_point.y - i;
			checkpoint.x = starting_point.x;
			available = check_space(player_board, checkpoint);
		}
		break;
	case 'e':
	case 'E':
		for (int i = 0; i < length && available; i++) {
			checkpoint.y = starting_point.y;
			checkpoint.x = starting_point.x + i;
			available = check_space(player_board, checkpoint);
		}
		break;
	case 's':
	case 'S':
		for (int i = 0; i < length && available; i++){
			checkpoint.y = starting_point.y + i;
			checkpoint.x = starting_point.x;
			available = check_space(player_board, checkpoint);
		}
		break;
	case 'w':
	case 'W':
		for (int i = 0; i < length && available; i++) {
			checkpoint.y = starting_point.y;
			checkpoint.x = starting_point.x - i;
			available = check_space(player_board, checkpoint);
		}
		break;
	default:
		break;
	}

	//if (!available)
	//	printf("Not enough space on board to place ship there.\n");
	return available;
}
void display_player_board(char player_board[][MAX_COL])
{
	printf("Player Board\n");
	printf("   0 1 2 3 4 5 6 7 8 9 \n");
	for (int i = 0; i < MAX_ROWS; i++) {
		printf(" %d ", i);
		for (int j = 0; j < MAX_COL; j++) {
			printf("%c ", player_board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void display_pc_board(char pc_board[][MAX_COL])
{
	printf("PC Board\n");
	printf("   0 1 2 3 4 5 6 7 8 9 \n");
	for (int i = 0; i < MAX_ROWS; i++) {
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