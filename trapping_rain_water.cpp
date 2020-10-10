// https://leetcode.com/problems/trapping-rain-water/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  int trap(vector<int>& height) {
    if (!height.size()) return 0;
    int i = 0, j = height.size() - 1, ans = 0;
    int lMax = height[i], rMax = height[j];
    while (i <= j) {
      lMax = max(lMax, height[i]);
      rMax = max(rMax, height[j]);
      if (lMax < rMax) {
        ans += lMax - height[i];
        i++;
      }
      else {
        ans += rMax - height[j];
        j--;
      }
    }
    return ans;
  }
};

int main() {
  Solution solution;
  vector<int> input{0,1,0,2,1,0,1,3,2,1,2,1};
  cout << solution.trap(input) << endl;
  return 0;
}
