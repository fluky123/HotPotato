#pragma once
#ifndef __umpire_h__
#define __umpire_h__

#include <vector>
#include "player.h"

class Umpire {
  // YOU MAY ADD
  void printer( Player::PlayerList &players);
  Player::PlayerList playerlist;
 public:
  Umpire( Player::PlayerList &players );
  void start();
};

#endif
