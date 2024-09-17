#pragma once
#include <string>

using namespace std;

class Game
{
private:

	int dice[6], diceCount, playerCount; // Initializes an array of dice values with an integer value of the amount of dice left

public:

	Game();

	string rules; // Stores the text from the rules text file

	// Setter & Getter methods for private variables to be used
	void setPlayerCount(int num);
	int getPlayerCount();
	void setDiceCount(int num);
	int getDiceCount();
	void setDice(int newDice, int num);
	int getDice(int index);

	// Methods to be used to run the game
	void displayRules();
	void rollDice();
	void reRoll();
	int calculateScore();
	int runGame();

};