// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:

  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    if (!root) return "";
    stringstream ss;
    ss << root->val;
    if (root->left || root->right) {
      ss << "(";
      ss << serialize(root->left);
      ss << ",";
      ss << serialize(root->right);
      ss << ")";
    }
    return ss.str();
  }

  int getSplitPos(string data) {
    int state = 0;
    for (int i=0; i<data.length(); i++) {
      if (data[i] == '(') state++;
      else if (data[i] == ')') state--;
      if (data[i] == ',' && state == 0) return i;
    }
    return -1;
  }

  tuple<int, string, string, bool> parse(string data) {
    int i = 0, j = data.length()-1;
    tuple<int, string, string, bool> invalid = {0, "", "", false};

    for (; i<data.length() && data[i] != '('; i++);
    int val;
    try {
      val = stoi(data.substr(0, i));
    } catch(invalid_argument) {
      return invalid;
    }
    if (i == data.length()) return {val, "", "", true};
    ++i;

    for (; j>=0 && data[j] != ')'; j--);
    if (j == -1) return invalid;
    --j;

    int splitPos = getSplitPos(data.substr(i, j-i+1));
    if (splitPos == -1) return invalid;

    return {val,
            data.substr(i, splitPos),
            data.substr(i+splitPos+1, j-i-splitPos), true};
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    auto [val, left, right, valid] = parse(data);
    if (!valid) return nullptr;
    TreeNode *node = new TreeNode(val);
    node->left = deserialize(left);
    node->right = deserialize(right);
    return node;
  }
};

int main() {
  Codec codec;
  cout << codec.serialize(codec.deserialize("1(2,3(#,-5))")) << endl;
  return 0;
}
