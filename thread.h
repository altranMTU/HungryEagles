//-----------------------------------------------------------------
// FILE NAME : Thread.h
// PROGRAM PURPOSE :
//  This program will allow multithreaded programming using
//  the thread.cpp file
//-----------------------------------------------------------------


#ifndef _THREAD_H
#define _THREAD_H

// header file
#include "ThreadClass.h"

//-----------------------------------------------------------------
// Process Thread Class:
//  Creates the mother eagle thread
//-----------------------------------------------------------------
class motherEagle : public Thread
{
 public:
  //constructor
  motherEagle(int M, int T, int *FeedingPots);

 private:
  void ThreadFunc(); //thread body
  int t;
  int m;
  int *feedingPots;
};

//-----------------------------------------------------------------
// Process Thread Class:
//  creates the baby eagle thread
//-----------------------------------------------------------------
class babyEagle : public Thread
{
 public:
  //constructor
  babyEagle(int I, int *FeedingPots, int M);

 private:
  void ThreadFunc(); //thread body
  int i;
  int m;
  int *feedingPots;
};

#endif
