/*
Potato.cc defines the type of potato used in the hot potato game. There are 2 types of potatoes
used: Mashed Potatoe and Fried Potato. Descriptions
will be provided in the file*/

//Includes all necessary files and C++ libraries
#include "potato.h"
#include "PRNG.h"
#include <iostream>
#include "umpire.h"
#include "player.h"
using namespace std;

extern PRNG(prng);//seen in p3driver.cc

//Ideas for improvement: could create a potato class which has numticks, reset() and countdown() function.
//Then can have mashed and fried potato as children where mashed potato is essentially a potato object
//Fried potato would contain an extra maxticks parameter and a virtual function for reset();

//Initialzie mashed potato. This potato contains the # of ticks (tosses) possible (# of ticks will be a random # between 1 to 10)
//and a reset function to reset the # of ticks when the round is over
Mashed::Mashed (unsigned int maxTicks)
{
  numticks = maxTicks;
  reset();
}

//Initialize fried potato. This potato contains a set # of ticks, a maximum # of ticks used to reset the potato and a reset function to reset to # of ticks when the round is over
Fried::Fried (unsigned int maxTicks)
{
  numticks = maxTicks;
  maxticks = maxTicks;
  reset();
}

//Generic Reset
void Potato::reset()
{
}

//Resets the potato to a random number of ticks with the maximum being 10
void Mashed::reset()
{
  numticks = prng(1,10);
  cout << " Mashed POTATO will go off after "<< numticks << " tosses" << endl;
}

//Reset the number of ticks to the maximum number of ticks given
void Fried::reset()
{
  numticks = maxticks;
  cout << " Fried POTATO will go off after "<< numticks << " tosses" << endl;
}

bool Potato::countdown(){
  if (numticks == 1)
    {
      return true;
    }
  else
    {
      numticks = numticks - 1;
      return false;
    }
}
