#include <bits/stdc++.h>

using namespace std;

struct Node {
  int idx, v;

  Node(int idx=0, int v=0) : idx(idx), v(v) {}

  bool operator<(const Node &t) const {
    return idx < t.idx;
  }
};

int main() {
  int n;
  cin >> n;
  vector<int> ary(n);
  for (int i=0; i<n; i++) {
    cin >> ary[i];
  }
  int m;
  cin >> m;
  vector<Node> cmds(2 * m);
  for (int i=0; i<m; i++) {
    int l, r, v;
    cin >> l >> r >> v;
    cmds[i * 2] = Node(l+1, v);
    cmds[i * 2 + 1] = Node(r, -v);
  }
  sort(cmds.begin(), cmds.end());
  int sum = 0, now = 0;
  for (int i=0; i<n; i++) {
    while(cmds[now].idx <= i) {
      sum += cmds[now].v;
      now++;
    }
    ary[i] += sum;
  }
  for (auto &v : ary) {
    cout << v << " ";
  }
  cout << endl;
  return 0;
}
