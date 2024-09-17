#include "Game.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

Game::Game() {
	int dice[6] = { 0 }; // Initializes an array of dice values
	int diceCount = 0; // Stores the amount of dice that are left in the play
	int playerCount = 0;
}

// Retrieves the player count
int Game::getPlayerCount() {
	return playerCount;
}

// Sets the player count
void Game::setPlayerCount(int num) {
	playerCount = num;
}

// Gets the amount of dice left to roll
int Game::getDiceCount() {
	return diceCount;
}

// Sets the total amount of dice left
void Game::setDiceCount(int num) {
	diceCount = num;
}

// Retrieves the dice values at a certain index
int Game::getDice(int index) {
	return dice[index];
}

// Sets the dice values at a certain index based on an integer input
void Game::setDice(int index, int num) {
	dice[index] = num;
}

void Game::displayRules() {
	ifstream myfile("FarkleRules.txt"); // Reads from the text file
	// While loop uses getline() to read every line from the file and then display the results
	while (getline(myfile, rules)) {
		cout << rules << endl;
	}
	cout << endl;

	myfile.close(); // Closes the file
}

// Roll function that initializes the values within the dice array to a random number between 1 and 6
void Game::rollDice() {

	setDiceCount(6);
	cout << "Dice Roll : ";

	for (int i = 0; i < 6; i++) {
		dice[i] = 1 + rand() % 6;
		cout << dice[i] << " ";
	}
	cout << endl;
}

// Reroll function that rerolls any dice still available after first roll using the boolean array
void Game::reRoll() {

	cout << "Reroll Dice: ";

	for (int i = 0; i < 6; i++) {
		if (dice[i] != 0) {
			dice[i] = 1 + rand() % 6;
			cout << dice[i] << " ";
		}
	}
	cout << endl;
}

// Function calculates the total score receive within their roll
int Game::calculateScore() {
	
	int threekindDie; // Stores the face-value that rolled three of a kind
	int totalPoints = 0; // Keep any points acquired during the round
	bool threekind = false; // Determines if the player rolled three of a kind
	string choice = ""; // Stores the player's option to continue rolling

	//Triple for-loop that begins with iterating through the dice, iteratively checking for a face value that occurs more than once.
	for (int a = 0; a < 6; a++) {
		for (int b = a + 1; b < 6; b++) {
			// If a second instance of a face value occurs, then the last for-loop checks for a third similar face value.
			if (dice[b] == dice[a] && dice[a] > 0) {
				for (int c = b + 1; c < 6; c++) {
					// If there's a third instance of a face value, then the score for the three of a kind is added, with the dice removed from the rest of the scoring and reroll pool
					if (dice[c] == dice[a]) {
						threekindDie = dice[a];
						threekind = true;
						dice[a] = 0, dice[b] = 0, dice[c] = 0;
						diceCount -= 3;
					}
				}
			}
		}
	}

	// If there's a three of a kind, then the points are added to the total score
	if (threekind) {
		cout << "You've rolled three " << threekindDie << "'s of a kind!" << endl << endl;
		if (threekindDie == 1) {
			totalPoints += 1000; // Adds 1000 points if the face value is 1
		}
		else {
			totalPoints = threekindDie * 100; // Otherwise, simply multiplies the face value by 100, and adds it to the total points
		}
	}

	// For-loop iterates through the dice values to find any 1's or 5's to add either 100 or 50 points for those face values
	for (int i = 0; i < 6; i++) {
		// Checks if dice contain a face value of 1 or 5, then removes the dice from the reroll pool and decreases the amount of dice available
		if (dice[i] == 1) {
			totalPoints += 100; // If the dice has a face value of 1, adds 100 points to the total
			dice[i] = 0;
			diceCount--;
		}
		else if (dice[i] == 5) {
			totalPoints += 50; // Otherwise, if the face value is a 5, then only adds 50 points to the total
			dice[i] = 0;
			diceCount--;
		}
	}

	return totalPoints;
}

int Game::runGame() {

	srand(time(0)); // Seeds the rand() function (random numbers)
	bool playing = true; // Boolean determines whether to keep playing the game

	while (playing) {

		int playerCount; // Stores the amount of players
		cout << "How many players will be playing? Must have a minimum of 2 players : ";
		cin >> playerCount; // Takes the user's input for the amount of players that will be playing
		// Checks to see if there's enough players to play the game
		if (playerCount > 1) {
			// Creates a vector for player objects
			vector<Player> players(playerCount);
			// For-loop creates player objects with their names and starting score depending on the amount of players, prompting user to enter the player's names
			for (int i = 0; i < players.size(); i++) {
				string name;
				cout << "Enter name for player " << i+1 << ": ";
				cin >> name;
				players[i] = Player(name, 0);
			}
			cout << endl << endl;
			// For-loop that iterates through the player object vector based on its size to roll dice and get the score until they've reached 1000 points
			for (int j = 0; j < players.size(); j++) {
				int currentScore = 0; // Stores the points obtained in one roll to successfully add to the player's score
				cout << "It's " << players[j].getName() << "'s turn!" << endl << endl;
				// While loop that loops until the player with the current turn reaches 1000 or more points to enter the game
				while (players[j].getScore() < 1000){
					rollDice();
					currentScore = calculateScore();
					// If the player rolled a totaled of 1000 points or greater, then they enter the game with the accumulated amount of points
					if (currentScore > 1000 || currentScore == 1000) {
						players[j].addScore(currentScore); // Sets the player's score
						cout << "----> " << players[j].getName() << " has entered the game with " << players[j].getScore() << " points!" << " <----" << endl << endl;
					}
					else {
						cout << "You obtained " << currentScore << " points this roll" << endl;
						cout << "Keep Rolling!" << endl << endl;
					}
				}
			}
			cout << "All players have now officially entered the game!" << endl << endl;

			
			bool noVictor = true; // Boolean variable that ensures there isn't a winner

			// Do-while-loop that keeps looping until a winner is present
			do {
				int currentScore = 0; // Keeps track of a player's score accumulated during their turn.
				// For-loop iterates through the player object vector a second time to officially begin the game with the first player's turn
				for (int k = 0; k < players.size(); k++) {

					string choice = ""; // Stores a string that dictates the choice the player chooses to roll again or keep their points 
					int reRollPoints; // Keeps track of any points accumulated during a reroll of the dice
					cout << "It's now " << players[k].getName() << "'s turn" << endl;
					rollDice(); // Calls the function to roll the dice
					currentScore = calculateScore(); // Uses the calculateScore function to determine how many points a player has earned for their first roll.

					// If the score is not 0, then the user will be prompted to keep rolling or keep their points , otherwise it's a farkle and passes up their turn by default
					if (currentScore != 0) {
						cout << "You've earned a total of " << currentScore << " points from this roll" << endl << endl;
						cout << "Would you want to roll again for more potentially more points? Input y or n (yes or no) : ";
						cin >> choice;
						cout << endl;
						// While-loop that initiates once the player has chosen to keep rolling after their initial roll during their turn
						while (currentScore > 0 && choice != "n") {
							reRoll(); // Calls the reRoll function to roll the remaining dice
							reRollPoints = calculateScore(); // Uses the calculateScore function once again to keep track of any points acquired with a re-roll
							// If during a reRoll the player rolls point-dice then they will have the option to acquire more points or keep rolling any remaining dice
							if (reRollPoints == 0 || getDiceCount() == 0) {
								// Checks if there's any remaining dice for the player to roll, otherwise it's a farkle if the player rolled no point dice during their reroll.
								if (getDiceCount() == 0) {
									cout << "You've ran out of dice to roll! Any points acquired have automatically been saved!" << endl << endl;
									currentScore += reRollPoints;
								}
								else {
									currentScore = 0;
									cout << "Farkle! You've earned no points this round and lost any points gained for rerolling!" << endl << endl;
								}
							} else {
								currentScore += reRollPoints;
								cout << "You've earned a total of " << currentScore << " points from this reroll" << endl;
								cout << "Would you want to roll again for more potentially more points? Input y or n (yes or no) : ";
								cin >> choice;
								cout << endl;
							}
						}

						// If the player inputs the option 'n' then their points are saved to their total score and pass up their turn onto the next player
						if (choice == "n") {
							players[k].addScore(currentScore);
							cout << "You've decided to pass, " << currentScore << " points have been saved to your score! ";
							cout << "You now have a total of " << players[k].getScore() << " points" << endl << endl;
						}
					} else {
						cout << "Farkle! You've earned no points this round" << endl << endl;
					}

					// Checks if a player has reached a score of 10000 or greater, then ends the game and declares a winner
					if (players[k].getScore() > 10000 || players[k].getScore() == 10000) {
						cout << players[k].getName() << " is the winner!" << endl << endl;
						noVictor = false; // Initiates the noVictor to true, to end the game's while loop
					}
				}
			} while (noVictor != false);
		} else {
			cout << "There isn't enough players! Try Again" << endl << endl;
		};

		playing = false; // Ends the game by default if all the game's loops have been exhausted
	}
	return 0;
}