#include <cstddef>
#include <iostream>
#include <thread>         // std::thread


#include "deque.h"

using namespace std;





void PushLeftWrok(int nrTimes, DQueue * que){
  for (int i = 0; i < nrTimes; i++){
    que->PushLeft(0);
  }
}

void PushAndPopWrok(int nrTimes, DQueue * que){
  for (int i = 0; i < nrTimes; i++){
    que->PushLeft(0);
    que->PopLeft();
  }
}


void PushLeftPopRightWrok(int nrTimes, DQueue * que){
  for (int i = 0; i < nrTimes; i++){
    que->PushLeft(0);
    que->PopRight();
  }
}



int main()
{
  DQueue que(false);
  int n = 2;
  int nrTimes = 10000;
  thread threads[n]; 
  for (int t = 0; t < n; t++) {
    threads[t] = thread(PushLeftWrok,nrTimes,&que);
  }
  for (int t = 0; t < n; t++) {
    threads[t].join();    
  }
}
