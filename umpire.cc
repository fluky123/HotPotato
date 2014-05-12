#include "PRNG.h"
#include "umpire.h"
#include "potato.h"
#include "player.h"
#include <iostream>
#include <string>
using namespace std;

extern PRNG(prng);
extern int numplayer;
int setcount = 1;

//This function prints out the ids of all the active players
void Umpire::printer(Player::PlayerList &players)
{
  cout <<" [";
  int size = playerlist.size();
  for (int i = 0 ; i < size; i++)
    {
        if (i != 0){
                cout << ",";
        }
      cout << playerlist[i]->getId();
    }
  cout << "]";
}

//This function is used to start the game
void Umpire::start()
{
  int size;
  unsigned int location;
  static int tempr;
  //Initializes the potatoes being used.
  Mashed a(10);
  Fried b(5);
  //Ensures that the right number of sets is played (till 1 player is left)
  while (playerlist.size() > 1)
    {
      tempr = 0;
      cout << endl;
      size = playerlist.size() - 1;
      //If the set uses the mashed potato
      if ((setcount % 2) == 1)
        {//If it is not the first set since you already define the number of ticks when you initialize the potato
          if (setcount != 1)
            {
              a.reset();
            }
          //random number to begin the tossing
          location = prng (0,size);
          cout << "Set " << setcount << "- User (mashed)" ; printer (playerlist); cout <<":";
          tempr = playerlist[location]->toss (a);
        }
      //If set uses fried potato
      else if ((setcount %2 )== 0)
        {//resets the number of ticks used
          b.reset();
          //random number to begin tossing
          location = prng (0, size);
          cout << "Set " << setcount << "- User (fried)" ; printer (playerlist);cout <<":";
          tempr = playerlist[location]->toss (b);
        }
      //prints the eliminated player
      if ((tempr % 2) == 0)
        {
          cout << "A("<< tempr << "). ";
        }
      else if ((tempr % 2) == 1)
        {
          cout <<"R("<< tempr <<"). ";
        }
      //This eliminates the player from the player list
      for (int i = 0 ; i <= size; i++)
        {
          int id2 = playerlist[i]->getId();
          if (id2 == tempr)
            {
              cout << "Eliminated: " << tempr << endl;
              delete playerlist[i];
              playerlist[i] = NULL;
              playerlist.erase (playerlist.begin() + i);
              break;
            }
        }
      //Goes to next set
      setcount++;
    }
  //Prints and eliminates the winner
  cout<< playerlist[0]->getId() << " wins the Match!"<<endl;
  delete playerlist[0];
}

Umpire::Umpire (Player::PlayerList &players)
{
  //initializes the playerlist used by both the umpire (to eliminate the last player tossed) and player (in order to know who it can toss to); Furthermore, creates all the players needed for this function
  for (int i = 0; i < numplayer; i++)
    {
      if (i % 2 == 0)
        {
          playerlist.push_back (new LRPlayer (i, playerlist));
        }

      else if (i % 2 == 1)
        {
          playerlist.push_back (new RNPlayer (i, playerlist));
        }
    }
}
