#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

// Default player constructor
Player::Player()
{
}

// Player constructor to set player's name and base score
Player::Player(string name, int num) {
	playerName = name;
	score = num;
}

// Sets a player's name
void Player::setName(string name) {
	playerName = name;
}

// Retrieves a player's name
string Player::getName() {
	return playerName;
}

// Sets a new score for the player based on a given integer
void Player::addScore(int num) {
	score += num;
}

// Gets the player's current score
int Player::getScore() {
	return score;
}