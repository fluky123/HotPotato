#pragma once
#ifndef __potato_H__
#define __potato_H__

class Potato {
 protected:
  int numticks;

 public:
  virtual void reset() = 0;     // must be defined in derived class
  bool countdown();
};

class Mashed : public Potato {
 public:
  Mashed( unsigned int maxTicks = 10 );
  void reset();
};

class Fried : public Potato {
  int maxticks;
 public:
  Fried( unsigned int maxTicks = 5);
  void reset();
};

#endif
