// https://leetcode.com/problems/merge-k-sorted-lists/

#include <bits/stdc++.h>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(initializer_list<int> l) : ListNode() {
    if (l.size()) val = *(l.begin());
    auto *ptr = this;
    for (const auto &item : l) {
      ptr->next = new ListNode(item);
      ptr = ptr->next;
    }
  }
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    ListNode *head = NULL, *ptr = NULL;
    vector<ListNode*> container;
    for (const auto &list: lists) {
      if (list) {
        container.push_back(list);
      }
    }
    auto comp = [](const ListNode *a, const ListNode *b) {
                  return a->val > b->val;
                };
    // make heap
    priority_queue<ListNode*, decltype(container), decltype(comp)> heap(comp, move(container));
    while (true) {
      if (heap.empty()) break;
      ListNode* minNode = heap.top();
      heap.pop();
      if (minNode->next) {
        heap.push(minNode->next);
      }
      if (!ptr) {
        head = minNode;
        ptr = minNode;
        continue;
      }
      ptr->next = minNode;
      ptr = minNode;
    }
    return head;
  }
};

void print(ListNode *node) {
  if (!node) return;
  cout << node->val << " ";
  print(node->next);
}

int main() {
  vector<ListNode*> input{new ListNode{1, 4, 5},
                          new ListNode{1, 3, 4},
                          new ListNode{1, 2, 3}};
  Solution solution;
  print(solution.mergeKLists(input));
  cout << endl;
  return 0;
}
