// https://leetcode.com/problems/daily-temperatures/submissions/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  vector<int> dailyTemperatures(vector<int>& ary) {
    // first: temp
    // second: idx
    stack<pair<int, int>> s;
    vector<int> ans(ary.size());
    for (int i=ary.size()-1; i>=0; i--) {
      while (s.size() && ary[i] >= s.top().first) {
        s.pop();
      }
      if (!s.size()) {
        ans[i] = 0;
      } else {
        ans[i] = s.top().second - i;
      }
      s.push({ary[i], i});
    }
    return ans;
  }
};

int main() {
  Solution solution;
  vector<int> input{73, 74, 75, 71, 69, 72, 76, 73};
  auto ans = solution.dailyTemperatures(input);
  for (const auto &item : ans) {
    cout << item << " ";
  }
  cout << endl;
  return 0;
}
