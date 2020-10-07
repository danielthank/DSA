#include <bits/stdc++.h>

using namespace std;

class Node {
public:
  Node() : wall(0) {}

  void open(int index) { wall |= (1 << index); }

  bool top() { return wall & (1 << 0); }

  bool down() { return wall & (1 << 1); }

  bool left() { return wall & (1 << 2); }

  bool right() { return wall & (1 << 3); }

private:
  int wall;
};

enum State {
            UNVISITED = 0,
            VISITING = 1,
            VISITED = 2,
};

class Maze {
public:
  Maze(int n, int m) : n(n), m(m) {
    mt = mt19937(rnd());
    grids.resize(n);
    for (int i=0; i<n; i++) {
      grids[i] = vector<Node>(m);
    }
  }

  void wilson() {
    vector<vector<State>> states;
    states.resize(n);
    for (int i=0; i<n; i++) {
      states[i] = vector<State>(m, UNVISITED);
    }
    states[0][0] = VISITED;
    for (int i=0; i<n; i++) {
      for (int j=0; j<m; j++) {
        if (states[i][j] == VISITED) continue;
        stack<pair<int, int>> visiting;
        auto now = make_pair(i, j);
        bool success = false;
        while (true) {
          int x = now.first, y = now.second;
          switch (states[x][y]) {
          case UNVISITED:
            states[x][y] = VISITING;
            visiting.push(make_pair(x, y));
            break;
          case VISITING:
            while (visiting.top() != now) {
              states[visiting.top().first][visiting.top().second] = UNVISITED;
              visiting.pop();
            }
            break;
          case VISITED:
            int nowx = x, nowy = y;
            while (!visiting.empty()) {
              int nextx = visiting.top().first, nexty = visiting.top().second;
              open_wall(nowx, nowy, nextx, nexty);
              states[nextx][nexty] = VISITED;
              visiting.pop();
              nowx = nextx, nowy = nexty;
            }
            success = true;
            break;
          }
          if (success) break;
          now = random_walk(x, y);
        }
      }
    }
  }

  void draw() {
    for (int i=0; i<n; i++) {
      for (int j=0; j<m; j++) {
        if (grids[i][j].top()) printf("+   ");
        else printf("+---");
      }
      printf("+\n");
      for (int j=0; j<m; j++) {
        if (grids[i][j].left()) printf("    ");
        else printf("|   ");
      }
      if (grids[i][m-1].right()) printf(" \n");
      else printf("|\n");
    }
    for (int j=0; j<m; j++) {
      if (grids[n-1][j].down()) printf("+   ");
      else printf("+---");
    }
    printf("+\n");
  }

private:
  const int go[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  int n, m;
  vector<vector<Node>> grids;
  random_device rnd;
  mt19937 mt;

  bool check(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
  }

  pair<int, int> random_walk(int x, int y) {
    uniform_int_distribution rand4(0, 3);
    while (1) {
      int t = rand4(mt);
      int xx = x + go[t][0];
      int yy = y + go[t][1];
      if (!check(xx, yy)) continue;
      // printf("walk: %d %d %d %d\n", x, y, xx, yy);
      return make_pair(xx, yy);
    }
  }

  void open_wall(int x, int y, int xx, int yy) {
    for (int i=0; i<4; i++) {
      if (x + go[i][0] == xx && y + go[i][1] == yy) {
        grids[x][y].open(i);
        grids[xx][yy].open(i ^ 1);
        break;
      }
    }
  }
};

int main() {
  int n, m;
  cin >> n >> m;
  Maze maze(n, m);
  maze.wilson();
  maze.draw();
}
