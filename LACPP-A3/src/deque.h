
#ifndef __X_H_deque__   // if x.h hasn't been included yet...
#define __X_H_deque__   






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

DQueue(bool print);

  void PushLeft(int val);

  void PushRight(int val);

  int PopLeft();

  int PopRight();

  void printQueFromRight();
};
#endif
