//-----------------------------------------------------------------
// NAME: Andrew Tran                             USER ID:altran
// DUE DATE: 3/17/2023
// PROGRAM ASSIGNMENT 4
// FILE NAME: thread.cpp
// PROGRAM PURPOSE :
// contains the functionality of the baby eagles and mother eagle
//-----------------------------------------------------------------
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "thread.h"

static Semaphore blockBaby("blockBaby", 0);
static Semaphore blockMother("blockMother", 0);
static Mutex check("check");
static Mutex check1("check1");
static Mutex check2("check2");
static int child = 0;
static int potsFilled = 0;
//-------------------------------------------------------------------
// Alg Thread function babyEagle:
// blocks the baby eagle if all feeding pots are empty, if one baby
// eagle find out the feeding pot is empty, mother wakes up
//-------------------------------------------------------------------
int ready_to_eat(int i, int m, int *feedingPots, int other)
{
  //if they haven't said they ready to eat or have just eaten
  char buf[100];
  if (other == 0){
    sprintf(buf, "Baby eagle %d is ready to eat.\n",i);
    write(1,buf,strlen(buf));
  }
  //looks if there are any filled feeding pots
  int j = 0;
  while(j<m){
    if(feedingPots[i] == 0){
      j++;
    }
    else{
      return 0;
    }
  }
  check.Lock();
  if (child == 0 && potsFilled == 0)
  {
    child = i;
    blockMother.Signal();
    sprintf(buf, "Baby eagle %d sees all feeding pots are empty and wakes up the mother.\n", child);
    write(1,buf,strlen(buf));
  }
  check.Unlock();
  blockBaby.Wait();
  return 0;
}

//-------------------------------------------------------------------
// Alg Thread function babyEagle:
// when a baby eagle is finished eating
//-------------------------------------------------------------------
int finish_eating(int i, int m, int *feedingPots)
{
  char buf[100];
  int j = 0;
  while(j<m)
  {

    //locks critical section
    check1.Lock();

    //if feedingPot is filled
    if (feedingPots[j] == 1){
      feedingPots[j]=0;
      potsFilled--;
      //baby eagles eats this pots and leaves loop
      sprintf(buf, "Baby eagle %d eating using feeding pot %d.\n",i ,j+1);
      write(1,buf,strlen(buf));
      sprintf(buf, "Baby eagle %d finishes eating.\n",i);
      write(1,buf,strlen(buf));
      check1.Unlock();
      return 0;
    }
    else{
      j++;
    }
    check1.Unlock();
  }
  //if game is done
  if (child < 0){
    return -1;
  }
  else{
    //if empty and mother eagle is sleeping
    check2.Lock();
    if (child == 0 && potsFilled == 0)
    {
      child = i;
      blockMother.Signal();
      sprintf(buf, "Baby eagle %d sees all feeding pots are empty and wakes up the mother.\n", child);
      write(1,buf,strlen(buf));
    }
    check2.Unlock();
    return 1;
  }
}

//-------------------------------------------------------------------
// Alg Thread function motherEagle:
// mother eagles goes to sleep
//-------------------------------------------------------------------
void goto_sleep()
{

  //mother goes to sleep
  char buf[100];
  child = 0;
  sprintf(buf, "Mother eagle takes a nap.\n");
  write(1,buf,strlen(buf));
  blockMother.Wait();
  return;
}

//-------------------------------------------------------------------
// Alg Thread function motherEagle:
// return when food is ready
//-------------------------------------------------------------------
void food_ready(int count, int m, int *feedingPots, int t)
{
  
  char buf[100];

  //mother gets food and fills the feeding pots
  sprintf(buf, "Mother eagle is awoke by baby eagle %d and starts preparing food.\n", child);
  write(1,buf,strlen(buf));
  potsFilled = m;
  for (int j = 0; j < m; j++){
    feedingPots[j] = 1;
  }

  //mother says its done for its mth feeding
  sprintf(buf, "Mother eagle says \" Feeding (%d)\" \n",count);
  write(1,buf,strlen(buf));

  //signals babies to go and eat
  for(int j = 0; j < m; j++)
  {
    blockBaby.Signal();
  }

  //signals the rest if the mother eagle retires
  if(count >= t)
  {
    child = -1;
    for(int j = 0; j<10000; j++)
    {
      blockBaby.Signal();
    }
  }
  
  //loops until the all childern have eaten
  while( potsFilled>0 ){
    //not sure why the loop doesn't work until this sprinf is in here
    sprintf(buf, "%d\n", potsFilled);
    //write(1,buf,strlen(buf));
  }
  return;
}
