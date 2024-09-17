#pragma once
#include <string>

using namespace std;

class Player
{
private:

	string playerName; // Stores player's name
	int score; // Records player's score

public:

	// Constructors to create a player object
	Player();
	Player(string name, int score);

	// Setter and getter methods for the player's name and score
	void setName(string name);
	string getName();
	void addScore(int score); 
	int getScore();


};