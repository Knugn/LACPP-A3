#include <cstddef>
#include <iostream>
#include <thread>         // std::thread
#include <ctime>
#include <cstdlib>
#include "deque.h"

using namespace std;





void PushLeftWrok(int nrTimes,int * counter,  DQueue * que){
  for (int i = 0; i < nrTimes; i++){
    while(*counter < nrTimes){
      que->PushLeft(0);
      __transaction_atomic
	{
	  (*counter)++;
	}
    }
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



int main(int argc, char *argv[])
{
  DQueue que(false);
  int n = 2;
  if (argc >= 2){
    n = atoi(argv[1]);
    std::cout << "threads set to: " << n << endl;
  }
  int nrCalculations = 1000000;
  thread threads[n]; 
  double timeTaken[n];
  int maxNrTimes = 10;


  for (int nrThread = 1; nrThread <= n; nrThread++){
    timeTaken[nrThread-1] = 0;
    for (int nrTimes = 0; nrTimes < maxNrTimes; nrTimes++){
      int counter = 0;
      auto t_start = std::chrono::high_resolution_clock::now();
      for (int t = 0; t < nrThread; t++) {
	threads[t] = thread(PushLeftWrok,nrCalculations,&counter,&que);
      }
      for (int t = 0; t < nrThread; t++) {
	threads[t].join();    
      }
      
      auto t_end = std::chrono::high_resolution_clock::now();
      double realTimeMs = std::chrono::duration<double, std::milli>(t_end-t_start).count();
      //std::cout << "time taken: " << realTimeMs << endl; 
      timeTaken[nrThread-1] += realTimeMs;
      que.freeQue();
    }

    timeTaken[nrThread-1] /= maxNrTimes;
  }//End of run
  for (int i = 0; i < n; i++){
    std::cout << "it took " << i+1 << " threads to finsih in: " << timeTaken[i] << endl;
  }
 
}
