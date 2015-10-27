#include <iostream>
#include <cstddef>

using namespace std;

int main () {
  bool run1 = false;
    __transaction_atomic
      {
	run1 = true;
	  __transaction_atomic
	    {
	      __transaction_cancel; 
	    }
      }
        cout << "the outer trasaction is not aborted doue to iner trasaction aborting " <<  run1 << endl;


	  
  bool run2 = false;
  bool run3 = false;
  
  __transaction_atomic
    {
     
      __transaction_atomic
	{
	  run2 = true;
	}
      if (run2){
	run3 = true;
      }
    }
  
  
  cout << "the inner trasaction can se changes done by the outer transaction " <<  run3 << endl;
  
  
}
