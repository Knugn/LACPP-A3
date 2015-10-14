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

public:

  DQueue()
  {
    leftSentinel = NULL;
    rightSentinel = NULL;

  }

  void PushLeft(int val)
  {
    QNode * newNode = new QNode();
    newNode->val = val; 
    __transaction_atomic
      {
	if (leftSentinel != NULL){
	  leftSentinel->left = newNode;
	  newNode->right = leftSentinel;
	}
	leftSentinel = newNode;
      }
  }

  void PushRight(int val)
  {
    QNode * newNode = new QNode();
    newNode->val = val; 
    __transaction_atomic
      {
	if (rightSentinel != NULL){
	  rightSentinel->right = newNode;
	  newNode->left = rightSentinel;
	}
	rightSentinel = newNode;
      }
  }

  int PopLeft()
  {
    // TODO
    return -1;
  }

  int PopRight()
  {
    // TODO
    return -1;
  }


  int main()
  {
    // cout << "program has started";
    DQueue * que = new DQueue();
    que->PushLeft(1);
    que->PushRight(1);
      return 0;
  }
};
