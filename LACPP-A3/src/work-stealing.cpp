#include <atomic>
#include <iostream>
#include <random>
#include <thread>
#include <unistd.h>

std::atomic<bool> terminate;

////////////////////////////////////////////////////////////////////////////////

#include "deque.h"

const int N = 4; // number of processors

DQueue job_queue[N];

int steelWork(int n){
  int value = -1;
  for (int i = 1; i < N; i++){
    //the process shood alweys try to take work from the next process
    int process = (n + i) % N; 
    __transaction_relaxed{
      value = job_queue[process].PopLeft();
    }
      if (value == -1){
	continue;
      }
      else if (value == 0){
	__transaction_relaxed{
	  job_queue[process].PushLeft(0);
	  continue;
	}
      }

      std::cout << "process " << n << " stell work from proses " << process << std::endl;
      return value;
    }
  return 0;
}

void processor(int n)
{
  while (!terminate)
    {
      int value;
      __transaction_relaxed{
	value = job_queue[n].PopLeft();
       }
      if (value == -1){
	value = steelWork(n);
      }
      //  sleep(value);
    }
}



////////////////////////////////////////////////////////////////////////////////

void user()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> processor(0, N-1);
  std::uniform_int_distribution<int> duration(0, 2*N);

  unsigned int time = 0;

  // generates a new job about once per second
  while (!terminate)
    {
      int p = processor(gen);
      int d = duration(gen);

      __transaction_relaxed
        {
	  //   std::cout << time << ": scheduling a job on processor " << p << " (duration: " << d << " s)." << std::endl;
          job_queue[p].PushRight(d);
        }

      //sleep(1);
      ++time;
    }
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
  std::thread user_thread(user);

  std::thread processors[N];
  for (int i=0; i<N; ++i)
    {
      processors[i] = std::thread(processor, i);
    }

  sleep(30);
  terminate = true;

  user_thread.join();
  for (int i=0; i<N; ++i)
    {
      processors[i].join();
    }

  return 0;
}
