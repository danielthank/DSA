// https://leetcode.com/problems/remove-invalid-parentheses/

#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
  string str;
  vector<string> ans;
  vector<bool> flag;
  void calc(int idx, int state, int left, int right) {
    if (idx == str.length()) {
      if (!left && !right) {
        string now;
        for (int i=0; i<str.length(); i++) {
          if (!flag[i]) now += str[i];
        }
        ans.push_back(now);
      }
      return;
    }
    if (str[idx] == '(') {
      if (left) {
        flag[idx] = true;
        calc(idx+1, state, left-1, right);
      }
      flag[idx] = false;
      calc(idx+1, state+1, left, right);

    } else if (str[idx] == ')') {
      if (right) {
        flag[idx] = true;
        calc(idx+1, state, left, right-1);
      }
      if (state) {
        flag[idx] = false;
        calc(idx+1, state-1, left, right);
      }
    } else {
      flag[idx] = false;
      calc(idx+1, state, left, right);
    }
  }
public:
  vector<string> removeInvalidParentheses(string s) {
    str = s;
    int left = 0, right = 0;
    for (int i=0; i<s.length(); i++) {
      if (str[i] == '(') left++;
      else if (str[i] == ')') {
        if (left) left--;
        else right++;
      }
    }
    ans.clear();
    flag = vector<bool>(str.length(), false);
    calc(0, 0, left, right);
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    return ans;
  }
};

int main() {
  Solution solution;
  string s = "(((()(()";
  auto ans = solution.removeInvalidParentheses(s);
  for (const auto &item: ans) {
    cout << item << endl;
  }
  return 0;
}
