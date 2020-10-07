#include <bits/stdc++.h>

using namespace std;

class CompareMax {
public:
  bool operator() (int x, int y) {
    return x < y;
  }
};

class CompareMin {
public:
  bool operator() (int x, int y) {
    return x > y;
  }
};

class MedianFinder {
public:
  /** initialize your data structure here. */
  MedianFinder() {}

  void addNum(int num) {
    max_heap.push(num);
    int max_size = max_heap.size();
    int min_size = min_heap.size();
    if (max_size && min_size) {
      int x = max_heap.top();
      int y = min_heap.top();
      if (x > y) {
        max_heap.pop();
        min_heap.pop();
        max_heap.push(y);
        min_heap.push(x);
      }
    }
    if (max_size - min_size > 1) {
      min_heap.push(max_heap.top());
      max_heap.pop();
    }
  }

  double findMedian() {
    int max_size = max_heap.size();
    int min_size = min_heap.size();
    if (max_size == min_size) return double(max_heap.top() + min_heap.top()) / 2;
    else return max_heap.top();
  }
private:
  priority_queue<int, vector<int>, CompareMax> max_heap;
  priority_queue<int, vector<int>, CompareMin> min_heap;
};

int main() {
  MedianFinder* obj = new MedianFinder();
  obj->addNum(-1);
  cout << obj->findMedian() << endl;
  obj->addNum(-2);
  cout << obj->findMedian() << endl;
  obj->addNum(-3);
  cout << obj->findMedian() << endl;
  obj->addNum(-4);
  cout << obj->findMedian() << endl;
  obj->addNum(-5);
  cout << obj->findMedian() << endl;
}
