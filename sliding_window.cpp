// https://leetcode.com/problems/longest-substring-without-repeating-characters/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  int lengthOfLongestSubstring(string str) {
    set<char> s;
    int pre = 0;
    int ans = 0;
    for (int i=0; i<str.length(); i++) {
      if (s.find(str[i]) != s.end()) {
        for (; pre<=i; pre++) {
          if (str[pre] == str[i]) break;
          s.erase(str[pre]);
        }
        pre++;
      } else {
        s.insert(str[i]);
      }
      ans = max(ans, i+1-pre);
    }
    return ans;
  }
};

int main() {
  string s;
  cin >> s;
  Solution solution;
  cout << solution.lengthOfLongestSubstring(s) << endl;
  return 0;
}
