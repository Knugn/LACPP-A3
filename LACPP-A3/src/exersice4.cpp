#include <cstddef>
#include <iostream>
#include <thread>         // std::thread
#include <ctime>
#include <cstdlib>
#include "deque.h"

using namespace std;

void exeption(){

  __transaction_atomic
    {
      throw 20;
    }

}


int main(int argc, char *argv[])
{
  try
    {
      exeption();
      cout << "no problems" << endl;
    }
  catch(int e)
    {
      cout << "a problem" << endl;
    }

}
