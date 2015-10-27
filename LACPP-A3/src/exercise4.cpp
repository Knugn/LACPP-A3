#include <iostream>
#include <cstddef>

using namespace std;

int main () {
  bool set = false;
  try
  {
    __transaction_atomic
      {
	set = true;
	throw 20;
      }
  }
  catch (int e)
  {
    cout << "An exception occurred. Exception Nr. " << e << '\n';
  }
  cout << "exeption commited the changes " << set << endl;
  return 0;
}
