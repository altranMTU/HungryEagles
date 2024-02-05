
//-------------------------------------------------------------
// PROGRAM PURPOSE:
// to create a program where a mother eagle sleeps and then the
// baby eagles wake her up and mother eagle fills the feeding
// pots and repeats till all are feedings are done
//--------------------------------------------------------------
#include <iostream>
#include "thread.h"
#include <string.h>

//--------------------------------------------------------------
// Function thread-main.cpp: main
//
// PARAMETER USAGE:
// used to get the number of feeding pots, babies, and number of 
// feedings
//--------------------------------------------------------------
int main(int argc, char *argv[])
{
    if (argc < 4)
    {
      cout << "Not enough arguments" << endl;
      exit(1);
    }
    //gets the command line arguments
    int m = atoi(argv[1]); //# of feeding pots
    int n = atoi(argv[2]); //# of childern
    int t = atoi(argv[3]); //# of feedings
    //places default value
    if(m == 0)
    {
      m = 10;
    }
    if(n == 0)
    {
      n = 10;
    }
    if(t == 0)
    {
      t = 10;
    }
    //tells the user the inputs that they inputed
    cout << "MAIN: There are " << n << " baby eagles, " << m << " feeding pots and " << t << " feedings." << endl;
    
    //initalizes the feeding pots to be 0 (empty)
    int *feedingPots = new int[m];

    for(int i = 0; i<m; i++)
    {
      feedingPots[i] = 0;
    }

    //inializes the babies and mothereagles
    babyEagle *babies[10000];
    motherEagle *mother = new motherEagle(m, t, feedingPots);
    for(int i = 0; i<n; i++)
    {
      babies[i] = new babyEagle(i+1, feedingPots, m);
    }
    cout << "MAIN: Game starts!!!!!" << endl;
    
    //starts and threads and waits for all the babies and mother to exit
    mother->Begin();
    for(int i = 0; i<n; i++)
    {
      babies[i]->Begin();
    }
    for(int i = 0; i<n; i++)
    {
      babies[i]->Join();
    }
    mother->Join();

    //tells user that the game is done
    cout << "Mother eagle retires after serving " << t << " feedings. Game is over!!!" << endl;
    Exit();
    return 0; 
}
