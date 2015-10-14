#include <cstddef>
#include <iostream>
#include "deque.cpp"









PushLeftWrok(int nrTimes, Deque * que){
  for (int i = 0; i < nrTimes; i++){
    que->PushLeft(0);
  }
}

PushAndPopWrok(int nrTimes, Deque * que){
  for (int i = 0; i < nrTimes; i++){
    que->PushLeft(0);
    que->PopLeft();
  }
}


PushLeftPopRightWrok(int nrTimes, Deque * que){
  for (int i = 0; i < nrTimes; i++){
    que->PushLeft(0);
    que->PopRight();
  }
}



int main()
{
  Deque deque(false);
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
