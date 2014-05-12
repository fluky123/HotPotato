/*
This is the main class to start the game
This program is meant to simulate a hot potato game with any number of players

There is a player class who's jub is to throw the potato
There is an umpire class to keep track of the number of tosses
There is a potato class that depending on the potato, will determine how many tosses is required before it goes off

A PRNG (Potato Random Number Generator) class is used to generate a random # in the case a random number is involved
*/
#include "potato.h"
#include "PRNG.h"
#include "player.h"
#include "umpire.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <vector>

using namespace std;

//declare necessary parameters
PRNG(prng); //to generate a constant which we will use to generate a random number
int numplayer; //# of players
Player::PlayerList players; //a list containing all the players

int main(int argc, char* argv[]){
  //If only argument is hotpotato, set default player and seed
  if ( argc == 1 )
  {
    numplayer = 5;
    prng.seed(5000);
  }
  //When hotpotato and numofplayers (with restrictions) are given, set default seed (to determine a random number)
  else if ( argc == 2 && atoi(argv[1]) >= 2 && atoi(argv[1]) <= 20 )
  {
    numplayer = atoi(argv[1]);
    prng.seed(5000);
  }
  //Check for invalid input
  else if ( argc > 3 || atoi(argv[1]) < 2 || atoi(argv[1]) > 20 || atoi(argv[2]) < 1 || atoi(argv[2]) > INT_MAX) 
  {
    cerr << "Invalid input." << endl;
    exit(1);
  }
  //Sets variables to given numbers
  else 
  {
    numplayer = atoi(argv[1]);
    prng.seed(atoi(argv[2]));
  }
 
  cout << numplayer << " players in the match" << endl;
  
  //Initializes umpire, players and starts the game
  Umpire ump (players);
  ump.start();
  return 0;
}

