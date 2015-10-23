#include <cstddef>
#include <iostream>
#include "deque.h"
using namespace std;


DQueue::DQueue()
  {

    leftSentinel = NULL;
    rightSentinel = NULL;

  }

  void DQueue::PushLeft(int val)
  {
    QNode * newNode = new QNode();
    newNode->val = val; 
    __transaction_atomic
      {
	if (leftSentinel != NULL){
	  leftSentinel->left = newNode;
	}
	newNode->right = leftSentinel;
	//If que was empty
	if (rightSentinel == NULL){
	  rightSentinel = newNode;
	}
	leftSentinel = newNode;
      }
  }

  void DQueue::PushRight(int val)
  {

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

  int DQueue::PopLeft()
  {
    QNode * temp;
    int val = 0;
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

  int DQueue::PopRight()
  {

    QNode * temp;
    int val = 0;
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

void DQueue::printQueFromRight(){

    QNode * temp = rightSentinel;
    while(temp != NULL){
      cout << "value of node is: " << temp->val << " \n";
      temp = temp->left;
    }
    cout << "\n"; 
  }

void DQueue::freeQue(){
  while (rightSentinel != NULL){
    QNode * temp = rightSentinel;
    rightSentinel = rightSentinel->left;
    delete temp;
  }
  rightSentinel = NULL;
  leftSentinel = NULL;
} 


/*

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
*/
