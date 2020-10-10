// https://leetcode.com/problems/longest-palindromic-substring/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  string longestPalindrome(string s) {
    int ans = 1;
    string ans_str = s.substr(0, 1);
    for (int i=0; i<s.length(); i++) {
      int l = i-1, r = i+1;
      while (l>=0 && r<s.length() && s[l] == s[r]) {
        if (r-l+1 > ans) {
          ans = r-l+1;
          ans_str = s.substr(l, ans);
        }
        l--, r++;
      }
      l = i, r = i+1;
      while (l>=0 && r<s.length() && s[l] == s[r]) {
        if (r-l+1 > ans) {
          ans = r-l+1;
          ans_str = s.substr(l, ans);
        }
        l--, r++;
      }
    }
    return ans_str;
  }
};

int main() {
  Solution solution;
  string s = "11211211";
  cout << solution.longestPalindrome(s) << endl;
  return 0;
}
