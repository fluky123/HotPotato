//Returns the ID of an LRPlayer
/*This file is creating a player object
A player object refers to the player in the hot
potato game */

//Includes all files and C++ libraries necessary
#include "PRNG.h"
#include "player.h"
#include "umpire.h"
#include "potato.h"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


extern PRNG(prng); //reading in the external PRNG parameter from p3driver.cc
vector<int>occurences;// tracks **something**
int initialcount = 0;

//default player constructor
Player::Player ()
        :id (0)
{
}

//player constructor when given parameters
Player::Player( unsigned int id, Player::PlayerList &players)
        :id(id),players(&players)
{
}

//returns ID of player
unsigned int Player::getId()
{
  return id;
}

//Generic player toss function
unsigned int Player::toss (Potato &potato)
{
  return 0;
}

//Constructor for RNPlayer
RNPlayer::RNPlayer ( unsigned int id, Player::PlayerList &players )
:Player(id,players)
{
}

//Constructor for LRPlayer
LRPlayer::LRPlayer ( unsigned int id, Player::PlayerList &players )
  :Player(id,players)
{
}

//Toss for Random Player (determines a random active player to toss to)
unsigned int RNPlayer::toss (Potato &potato)
{
  unsigned int next;
  int size = (*players).size()-1;
  int id2;
  //while the potato hasnt run out of time yet
  if (! (potato.countdown()))
    {
      //prints the current player
      if ((id % 2) == 1)
        {
          cout << "R(" << id << "), " ;
        }

      else if ((id % 2) == 0)
        {
          cout << "A(" << id << "), ";
        }
      //determines a random active player to throw it to that is not itself
      do
        {
          next = prng(0, size);
          id2 = (*players)[next]->getId();
        } while (id2 == id);

    }
  //once the number of ticks has been reached
  else if (potato.countdown())
    {
      return id;
    }
  //else call for the next toss
  return (*players)[next]->toss (potato);
}

//Toss for LRPlayer (pass to left or right depending on number of occurences)
unsigned int LRPlayer::toss (Potato &potato)
{
  int size, location;
  size = (*players).size() - 1;
  //if this is the first run to create the vector of occurences
  if (initialcount == 0)
    {
      for (int j = 0; j <= size; j++)
        {
          occurences.push_back (0);
        }
      //to ensure this vector is only created once
      initialcount++;
    }
  //if within the number of ticks
  if (! (potato.countdown()))
    {
      //prints the current player accordingly
      if ((id % 2) == 1)
        {
          cout << "R(" << id << "), ";
        }

      else if ((id % 2) == 0)
        {
          cout << "A(" << id << "), ";
        }
      //determines the location of the current player on the playerlist
      for (int i = 0 ;i <= size ; i++)
        {
          int id2 = (*players)[i]->getId();
          if (id2 == id)
            {
              location = i;
              break;
            }
   }
      //if the player will toss to the left and it is the first element of the array, it tosses to the last player in the array
      if ((occurences[id] % 2) == 0 && location == 0 )
        {
          occurences[id]++;
          location = size;
        }
      //ensures player tosses it to the left
      else if ((occurences[id] % 2) == 0)
        {
          occurences[id]++;
          location = location -1;
        }
      //if player tosses to the right and it is the last element of the array, it tosses to the first player on the array
      else if ((occurences[id] % 2) == 1 && location == size)
        {
          occurences[id]++;
          location = 0;
        }
      //ensures toss is to the right
      else if ((occurences[id] % 2)== 1)
        {
          occurences[id]++;
          location = location + 1;
        }
      //in all cases above, ensures occurence has been accounted for
    }
  //returns id of eliminated player
  else if (potato.countdown())
    {
      return id;
    }
  //else return the next toss
  return (*players)[location]->toss (potato);
}
