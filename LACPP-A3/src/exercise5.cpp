#include <iostream>
#include <cstddef>

using namespace std;

int main () {
  bool run1 = false;
  bool run2 = false;
  bool run3 = false;
    __transaction_atomic
      {
	run1 = true;
	  __transaction_atomic
	    {
	      run2 = true;
	      __transaction_cancel; 
	    }
	  run3 = true;
      }
    cout << "the outer trasaction is commited " <<  run1 << endl;
    cout << "the inner trasaction is commited " <<  run2 << endl;
    cout << "the outer transaction is committed after the inner transaction has raised an exception " <<  run3 << endl;
    
  
}
