#pragma once

#ifndef __player_h__
#define __player_h__
#include <vector>
#include "potato.h"
using namespace std;

class Player {
 protected:
  Player();

 public:
  typedef vector<Player*> PlayerList; // container type of your choice of players
  int id;
  Player::PlayerList* players;
  Player( unsigned int id, Player::PlayerList &players);
  unsigned int getId();
  virtual unsigned int toss( Potato &potato ) = 0; // must be defined in derived class
};

class RNPlayer : public Player {
 public:
  RNPlayer(unsigned int id, Player::PlayerList &players );
  unsigned int toss( Potato &potato );
};

class LRPlayer : public Player {
 public:
  LRPlayer( unsigned int id, Player::PlayerList &players );
  unsigned int toss( Potato &potato );
};

#endif
