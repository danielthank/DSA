#include <bits/stdc++.h>

using namespace std;

template<typename K, typename V>
class AVLTree {
public:
  struct Node {
    Node(K key, V val) : key(key), val(val), left(NULL), right(NULL), height(1) {}

    K key;
    V val;
    Node *left;
    Node *right;
    int height;
  } *root;

  AVLTree() : root(NULL) {}

  void Insert(K key, V val) {
    root = _Insert(root, key, val);
  }

  void Delete(Node *target) {
    root = _Delete(root, target);
  }

  void Print() {
    _Print(root);
    cout << endl;
  }

private:

  static int GetHeight(Node *node) {
    if (!node) return 0;
    return node->height;
  }

  static int GetBalanceFactor(Node *node) {
    if (!node) return 0;
    return GetHeight(node->left) - GetHeight(node->right);
  }

  static Node *_Insert(Node *node, K new_key, V new_val) {
    if (!node) return new Node(new_key, new_val);
    if (new_key < node->key) {
      node->left = _Insert(node->left, new_key, new_val);
    } else {
      node->right = _Insert(node->right, new_key, new_val);
    }
    UpdateHeight(node);
    int balance_factor = GetBalanceFactor(node);
    if (balance_factor > 1) {
      if (new_key < node->left->key) {
        // left-left
        return RightRotate(node);
      } else {
        // left-right
        node->left = LeftRotate(node->left);
        return RightRotate(node);
      }
    } else if (balance_factor < -1) {
      if (new_key < node->right->key) {
        // right-left
        node->right = RightRotate(node->right);
        return LeftRotate(node);
      } else {
        // right-right
        return LeftRotate(node);
      }
    }
    return node;
  }

  static Node *GetMin(Node *node) {
    if (!node) return NULL;
    if (node->left) return GetMin(node->left);
    return node;
  }

  static Node *_Delete(Node *node, Node *target) {
    if (!node) return NULL;
    auto *now = node;
    if (target->key < node->key) {
      node->left = _Delete(node->left, target);
    } else if (target->key > node->key) {
      node->right = _Delete(node->right, target);
    } else {
      if (target->val != node->val) {
        node->right = _Delete(node->right, target);
      } else {
        if (node->left && node->right) {
          Node *min_node = GetMin(node->right);
          swap(node->key, min_node->key);
          swap(node->val, min_node->val);
          node->right = _Delete(node->right, target);
        } else if(node->left) {
          now = node->left;
          delete node;
        } else if(node->right) {
          now = node->right;
          delete node;
        } else {
          now = NULL;
          delete node;
        }
      }
    }

    UpdateHeight(now);
    int balance_factor = GetBalanceFactor(now);

    if (balance_factor > 1) {
      if (node->left->left->height >= node->left->right->height) {
        // left-left
        return RightRotate(now);
      } else {
        // left-right
        node->left = LeftRotate(node->left);
        return RightRotate(now);
      }
    } else if (balance_factor < -1) {
      if (node->right->left->height <= node->right->right->height) {
        // right-left
        node->right = RightRotate(node->right);
        return LeftRotate(now);
      } else {
        // right-right
        return LeftRotate(now);
      }
    }
    return now;
  }

  static void UpdateHeight(Node *node) {
    if (!node) return;
    node->height = max(GetHeight(node->left), GetHeight(node->right)) + 1;
  }

  static Node *RightRotate(Node *z) {
    Node *y = z->left;
    z->left = y->right;
    y->right = z;
    UpdateHeight(z);
    UpdateHeight(y);
    return y;
  }

  static Node *LeftRotate(Node *z) {
    Node *y = z->right;
    z->right = y->left;
    y->left = z;
    UpdateHeight(z);
    UpdateHeight(y);
    return y;
  }

  static void _Print(Node *node) {
    if (!node) return;
    cout << "(" << node->key << ", " << node->val << ") ";
    if (node->left) _Print(node->left);
    if (node->right) _Print(node->right);
  }
};

int main() {
  AVLTree<int, string> t;
  t.Insert(10, "val10");
  t.Print();
  t.Insert(20, "val20");
  t.Print();
  t.Insert(30, "val30");
  t.Print();
  t.Insert(40, "val40");
  t.Print();
  t.Insert(50, "val50");
  t.Print();
  t.Insert(25, "val25");
  t.Print();
  t.Insert(5, "val5");
  t.Print();
  t.Insert(1, "val1");
  t.Print();
  t.Delete(new AVLTree<int, string>::Node(30, "val30"));
  t.Print();
  t.Delete(new AVLTree<int, string>::Node(20, "val20"));
  t.Print();
  t.Delete(new AVLTree<int, string>::Node(1, "val1"));
  t.Print();
  t.Delete(new AVLTree<int, string>::Node(10, "val10"));
  t.Print();
  t.Delete(new AVLTree<int, string>::Node(25, "val25"));
  t.Print();
  t.Delete(new AVLTree<int, string>::Node(50, "val50"));
  t.Print();
  t.Delete(new AVLTree<int, string>::Node(5, "val5"));
  t.Print();
  t.Delete(new AVLTree<int, string>::Node(40, "val40"));
  t.Print();
  t.Insert(50, "val50");
  t.Print();
  t.Insert(25, "val25");
  t.Print();
  t.Delete(new AVLTree<int, string>::Node(25, "val25"));
  t.Print();
  t.Insert(5, "val5");
  t.Print();
  t.Delete(new AVLTree<int, string>::Node(50, "val50"));
  t.Print();
  t.Insert(1, "val1");
  t.Print();
  t.Delete(new AVLTree<int, string>::Node(5, "val5"));
  t.Print();
  t.Delete(new AVLTree<int, string>::Node(1, "val1"));
  t.Print();
  return 0;
}
