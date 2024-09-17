/*
* 
* Name : Kevin Caballero
* Data : 12/05/2023
* Description: The following program, calls a few functions to run a full game loop of the game Farkle.
* Farkle is a multiplayer dice game that requires a minimum of two players to play, while have no limit
* as to the most amount of players there can be in the game. The goal is for one of the players to reach 10,000
* points in total as a result of rolling 6 dice with certain scenarios that can result in the player gaining
* or losing points acquired during their turn. The program begins by displaying the rules, creating the player's
* profile, and finally, running the game until a player is declared the winner.
* 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Game.h"
#include "Player.h"

using namespace std;


int main()
{
    srand(time(0)); // Seeds the rand() function (random numbers)
    Game game; // Creates a game object of the "Game" class
    game.displayRules(); // Function that displays the game's rules onto the console to the user
    game.runGame(); // Runs the game loop

    return 0;
}