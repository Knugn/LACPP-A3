#include <cstddef>
#include <iostream>
#include <thread>         // std::thread
#include <ctime>
#include "deque.h"

using namespace std;





void PushLeftWrok(int * counters, int nrTimes , DQueue * que){
  //race condition in first row, however its not big problem
  while(*counters < nrTimes){
    que->PushLeft(0);
    __transaction_atomic{
      (*counters)++;
    }
  }
}

void PushAndPopWrok(int * counters, int nrTimes  ,DQueue * que){  
  //race condition in first row, however its not big problem
  while(*counters < nrTimes){
    que->PushLeft(0);
    que->PopLeft();
    __transaction_atomic{
      (*counters)++;
    }
  }
}


void PushLeftPopRightWrok(int * counters, int nrTimes,  DQueue * que){
  //race condition in first row, however its not big problem
  while(*counters < nrTimes){
    que->PushLeft(0);
    que->PopRight();
    __transaction_atomic{
      (*counters)++;
    }
  }
}



int main()
{
  DQueue que(false);
  int n = 1;
  int nrTimes = 10000000;
  int counter = 0;
  thread threads[n]; 

  auto t_start = std::chrono::high_resolution_clock::now();

  for (int t = 0; t < n; t++) {
    threads[t] = thread(PushLeftWrok,&counter ,nrTimes,&que);
  }
  for (int t = 0; t < n; t++) {
    threads[t].join();    
  }

  auto t_end = std::chrono::high_resolution_clock::now();
  
  double realTimeMs = std::chrono::duration<double, std::milli>(t_end-t_start).count();
  cout << "time taken: " << realTimeMs << "\n";
}
