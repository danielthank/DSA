// https://leetcode.com/problems/jump-game/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  bool canJump(vector<int>& nums) {
    int potential = 0;
    for (int i=0; i<nums.size()-1; i++) {
      potential = max(potential, nums[i]);
      if (potential == 0) return false;
      potential--;
    }
    return true;
  }
};

class Solution2 {
public:
  bool canJump(vector<int>& nums) {
    int i = 0;
    while (i + nums[i] < nums.size() - 1) {
      int max_index = i;
      for (int j=i; j<=i + nums[i]; j++) {
        if (j + nums[j] > max_index + nums[max_index]) {
          max_index = j;
        }
      }
      if (max_index + nums[max_index] <= i + nums[i]) return false;
      i = max_index;
    }
    return true;
  }
};

int main() {
  Solution solution;
  vector<int> input{2,3,1,1,4};
  cout << solution.canJump(input) << endl;
  return 0;
}
