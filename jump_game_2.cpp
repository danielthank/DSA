// https://leetcode.com/problems/jump-game-ii/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  int jump(vector<int>& nums) {
    if (nums.size() <= 1) return 0;
    int i = 0, ans = 0, pre = -1;
    while (i + nums[i] < nums.size() - 1) {
      int max_index = pre;
      for (int j=pre+1; j<=i + nums[i]; j++) {
        if (j+nums[j] > max_index+nums[max_index])
          max_index = j;
      }
      pre = i+nums[i];
      i = max_index;
      ans ++;
    }
    return ans + 1;
  }
};

int main() {
  Solution solution;
  vector<int> input{2,3,1,1,4};
  cout << solution.jump(input) << endl;
  return 0;
}
