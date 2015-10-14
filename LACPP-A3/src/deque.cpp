#include <cstddef>
#include <iostream>

using namespace std;

class DQueue
{
  struct QNode
  {
    QNode *left, *right;
    int val;
  };

  QNode *leftSentinel, *rightSentinel;
  bool print;
public:

  DQueue(bool print)
  {
    this->print = print;
    leftSentinel = NULL;
    rightSentinel = NULL;

  }

  void PushLeft(int val)
  {
    if (print){
      cout << "left adding: " << val << "\n";
    }
    QNode * newNode = new QNode();
    newNode->val = val; 
    __transaction_atomic
      {
	if (leftSentinel != NULL){
	  leftSentinel->left = newNode;
	  newNode->right = leftSentinel;
	}
	//If que was empty
	if (rightSentinel == NULL){
	  rightSentinel = newNode;
	}
	leftSentinel = newNode;
      }
  }

  void PushRight(int val)
  {
    if (print){
      cout << "right adding: " << val << "\n";
    }
    QNode * newNode = new QNode();
    newNode->val = val; 
    __transaction_atomic
      {
	if (rightSentinel != NULL){
	  rightSentinel->right = newNode;
	  newNode->left = rightSentinel;
	}
	//If que was empty
	if (leftSentinel == NULL){
	  leftSentinel = newNode;
	}
	rightSentinel = newNode;
      }
  }

  int PopLeft()
  {
    if (print){
      cout << "left poping \n";
    }
    QNode * temp;
    int val;
    if (leftSentinel == NULL){
      return -1;
    }
    __transaction_atomic
      {
	val = leftSentinel->val;
	temp = leftSentinel;
	leftSentinel = leftSentinel->right;
	//if que not empty
	if (leftSentinel != NULL){
	  leftSentinel->left = NULL;
	}else{
	  rightSentinel = NULL;
	}
	
      }
    delete temp;
    return val;
  }

  int PopRight()
  {
    if (print){
      cout << "right poping \n";
    }
    QNode * temp;
    int val;
    if (rightSentinel == NULL){
      return -1;
    }
    __transaction_atomic
      {
	val = rightSentinel->val;
	temp = rightSentinel;
	rightSentinel = rightSentinel->left;
	//if que not empty
	if (rightSentinel != NULL){
	  rightSentinel->right = NULL;
	}else{
	  leftSentinel= NULL;
	}

      }
    delete temp;
    return val;
  }

  void printQueFromRight(){
    if (rightSentinel == NULL){
      cout << "que is empty \n";
    }
    QNode * temp = rightSentinel;
    while(temp != NULL){
      cout << "value of node is: " << temp->val << " \n";
      temp = temp->left;
    }
    cout << "\n"; 
  }
};



int main()
{
  cout << "program has started \n";
  DQueue * que = new DQueue(true);
  que->PushLeft(1);
  que->printQueFromRight();

  que->PushRight(2);
  que->printQueFromRight();

  que->PopRight();
  que->printQueFromRight();

  que->PushLeft(25);
  que->printQueFromRight();

  que->PopRight();
  que->printQueFromRight();
  return 0;
}
