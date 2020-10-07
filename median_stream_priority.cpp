#include <bits/stdc++.h>

using namespace std;

template<typename T, bool (*comp)(T, T)>
class heap {
public:
  heap() {}

  const T& top() const {
    return d.front();
  }

  void push(const T &value) {
    d.push_back(value);
    int c = d.size() - 1;
    T v = d[c];
    while (c > 0) {
      int p = (c-1) / 2;
      if (!comp(d[p], v)) break;
      d[c] = d[p];
      c = p;
    }
    d[c] = v;
  }

  void pop() {
    int len = d.size()-1;
    if (len > 0) {
      T v = d.back();
      d.back() = d.front();
      int p = 0;
      for (int c=1; c<len; c=p*2+1) {
        if (c+1 < len && comp(d[c], d[c+1])) {
          ++c;
        }
        if (!comp(v, d[c])) break;
        d[p] = d[c];
        p = c;
      }
      d[p] = v;
    }
    d.pop_back();
  }

  int size() const {
    return d.size();
  }

private:
  vector<T> d;
};

bool comp_min(int x, int y) {
  return x > y;
}

bool comp_max(int x, int y) {
  return x < y;
}

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
  heap<int, comp_max> max_heap;
  heap<int, comp_min> min_heap;
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
