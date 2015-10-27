#include <atomic>
#include <cstddef>
#include <iostream>
#include <thread>         // std::thread
#include <ctime>
#include <cstdlib>
#include "deque.h"
#include <unistd.h>

//using namespace std;


std::atomic<bool> terminate;

void PushLeftWrok(int * counter,  DQueue * que){
  int c = 0;
  while(!terminate){
    que->PushLeft(0);
    c++;
  }
  *counter = c;
}

void PushAndPopWrok(int * counter,  DQueue * que){
    int c = 0;
    while(!terminate){
      que->PushLeft(0);
      que->PopLeft();
      c++;
      }
    *counter = c;
}


void PushLeftPopRightWrok(int * counter,  DQueue * que){

    int c = 0;
    while(!terminate){
    que->PushLeft(0);
    que->PopRight();
    c++;
  }
    *counter = c;
  
}



int main(int argc, char *argv[])
{
  int n = 2;
  int work = 0;
  if (argc >= 2){
    n = atoi(argv[1]);
    std::cout << "threads set to: " << n << std::endl;
  }

  if (argc >= 3){
    work = atoi(argv[2]);
    std::cout << "work set to: " << work << std::endl;
  }
  int sleepTime = 1;
  std::thread threads[n]; 
  double nrCounts[n];
  int counter[n];
  int maxNrTimes = 10;
  DQueue que;

  for (int nrThread = 1; nrThread <= n; nrThread++){
    nrCounts[nrThread-1] = 0;
    for (int nrTimes = 0; nrTimes < maxNrTimes; nrTimes++){
      int total = 0;
      for (int t = 0; t < nrThread; t++) {
	counter[t] = 0;
	switch (work)
	  {
	  case 0:
	    threads[t] = std::thread(PushLeftWrok,&counter[t],&que);
	    break;
	  case 1:
	    threads[t] = std::thread(PushAndPopWrok,&counter[t],&que);
	    break;
	  case 2:
	    threads[t] = std::thread(PushLeftPopRightWrok,&counter[t],&que);
	    break;
	  }
      }
      sleep(sleepTime);
      terminate = true;
      for (int t = 0; t < nrThread; t++) {
	threads[t].join();
	total += counter[t];
      }
      terminate = false;
      
      nrCounts[nrThread-1] += total;
      que.freeQue();  
    }

    nrCounts[nrThread-1] /= maxNrTimes;
  }//End of run
  std::cout << "problem time in s is " << sleepTime  << std::endl;
  
  switch (work)
    {
    case 0:
      std::cout << "problem is PushLeftWrok" << std::endl;
      break;
    case 1:
      std::cout << "problem is PushAndPopWrok" << std::endl;
      break;
    case 2:
      std::cout << "problem is PushLeftPopRightWrok" << std::endl;
      break;
    }
  for (int i = 0; i < n; i++){
    std::cout << i+1 << " threads finsihed: " << nrCounts[i] << " computations" << std::endl;
  }

}
