//-----------------------------------------------------------------
// FILE NAME: thread.cpp
// PROGRAM PURPOSE :
// contains the class  implementations of the baby eagles and 
// mother eagle
//-----------------------------------------------------------------
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "thread.h"
#include "thread-support.cpp"


//------------------------------------------------------------------
// AlgThread Class:
// constructor for mother Eagle thread
//------------------------------------------------------------------
motherEagle::motherEagle(int M, int T, int *FeedingPots) 
{
  m = M;
  t = T;
  feedingPots = FeedingPots;
}
//------------------------------------------------------------------
// AlgThread Class:
// constructor for baby eagle thread
//------------------------------------------------------------------
babyEagle::babyEagle(int I, int *FeedingPots, int M) 
{
 i = I;
 m = M;
 feedingPots = FeedingPots;
}

//-------------------------------------------------------------------
// Alg Thread class body motherEagle:
// sleeps first and becomes awake when baby wake her up and fills the
// feeding pots at a delay and retires after doing its feedings
//-------------------------------------------------------------------
void motherEagle::ThreadFunc()
{
  Thread::ThreadFunc();
  char buf[100];
  sprintf(buf, "Mother eagle started\n");
  write(1,buf,strlen(buf));
  int count = 0;
  while(count < t)
  {
    count++;
    goto_sleep();
    Delay();
    food_ready(count, m, feedingPots, t);
    Delay();
  }
  child = -1;
  Exit();
}

//-------------------------------------------------------------------
// Alg Thread class body babyEagle:
// constant waits and eats once ready
//-------------------------------------------------------------------
void babyEagle::ThreadFunc()
{
  Thread::ThreadFunc();
  char buf[100];
  int check = 0;
  sprintf(buf, "Baby eagle %d started\n",i);
  write(1,buf,strlen(buf));
  while (1){
    Delay();
    ready_to_eat(i, m, feedingPots, check);
    Delay();
    check = finish_eating(i, m, feedingPots);
    if (check < 0){
      break;
    }

  }
  Exit();
}