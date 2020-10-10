// https://leetcode.com/problems/3sum/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> ans;
    if (nums.size() < 3) return ans;
    sort(nums.begin(), nums.end());
    for (int i=0; i<nums.size(); i++) {
      int l = i+1, r = nums.size()-1;
      while (l < r) {
        int result = nums[i] + nums[l] + nums[r];
        if (result < 0) l++;
        else if (result > 0) r--;
        else {
          ans.push_back(vector<int>{nums[i], nums[l], nums[r]});
          while (l+1 < nums.size() && nums[l] == ans.back()[1]) l++;
          while (r-1 > i && nums[r] == ans.back()[2]) r--;
        }
      }
      while (i+1<nums.size() && nums[i] == nums[i+1]) i++;
    }
    return ans;
  }
};

int main() {
  vector<int> input{0, 0, 0, 0};
  Solution solution;
  auto ans = solution.threeSum(input);
  for (const auto &item: ans) {
    for (const auto &num : item) {
      cout << num << " ";
    }
    cout << endl;
  }
  return 0;
}
