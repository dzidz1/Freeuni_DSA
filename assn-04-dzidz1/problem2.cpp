#include <bits/stdc++.h>
using namespace std;
using lli = long long;

#define MAXN 1000020

lli res, max_subtree_path[MAXN], max_path_from_node[MAXN], out_path[MAXN];
int i, j, k, N, parent[MAXN], parent_distance[MAXN], cycle_start, cycle_end,
    dist, Stack[MAXN], stack_size, it[MAXN], cycle_visited[MAXN];
int visited[MAXN], onpath[MAXN];
vector<pair<int, int>> adj_list[MAXN];

void constr_graph(int N) {
  for (i = 0; i < N; i++) {
    cin >> j >> k;
    j--;
    if (j >= 0 && j < N) {
      pair<int, int> p1 = {j, k};
      pair<int, int> p2 = {i, k};
      adj_list[i].push_back(p1);
      adj_list[j].push_back(p2);
    }
  }
}

void dfs(int source) {
  int v, u;
  lli second_longest_path;

  Stack[stack_size++] = source;

  while (stack_size) {
    v = Stack[stack_size - 1];

    if (!visited[v]) {
      visited[v] = 1;
      it[v] = -1;
    }

    for (++it[v]; it[v] < (int)adj_list[v].size(); ++it[v]) {
      u = adj_list[v][it[v]].first;
      if (!cycle_visited[v] && u == parent[v]) {
        cycle_visited[v] = 1;
        adj_list[v][it[v]].first = -1;
        continue;
      }
      if (visited[u]) {
        if (visited[u] == 2) {
          adj_list[v][it[v]].first = -1;
          continue;
        }
        cycle_start = v;
        cycle_end = u;
        dist = adj_list[v][it[v]].second;
        onpath[v] = 1;
        adj_list[v][it[v]].first = -1;
        continue;
      }

      parent[u] = v, parent_distance[u] = adj_list[v][it[v]].second;
      Stack[stack_size++] = u;
      break;
    }

    if (it[v] < (int)adj_list[v].size())
      continue;

    visited[v]++;

    second_longest_path = 0;
    for (int i = 0; i < (int)adj_list[v].size(); i++) {
      u = adj_list[v][i].first;
      if (u < 0)
        continue;
      onpath[v] |= onpath[u];
      max_subtree_path[v] = max(max_subtree_path[u], max_subtree_path[v]);

      if (max_path_from_node[u] + parent_distance[u] > max_path_from_node[v]) {
        second_longest_path = max_path_from_node[v];
        max_path_from_node[v] = max_path_from_node[u] + parent_distance[u];
      } else {
        second_longest_path = max(second_longest_path,
                                  max_path_from_node[u] + parent_distance[u]);
      }

      if (!onpath[u]) {
        out_path[v] =
            max(out_path[v], max_path_from_node[u] + parent_distance[u]);
      }
    }

    max_subtree_path[v] =
        max(max_subtree_path[v], max_path_from_node[v] + second_longest_path);
    stack_size--;
  }
}

lli calculate_max_cycle_path() {
  // if (cycle_start < 0 || cycle_end < 0 && cycle_start == cycle_end) return 0;
  int v;
  lli length, append, total, tmp, back;

  v = cycle_start;
  length = 0;
  append = 0;
  tmp = 0;
  total = 0;

  while (v != cycle_end) {
    append = max(append, length + out_path[v]);
    length += parent_distance[v];
    v = parent[v];
  }
  tmp = dist + append;

  v = cycle_end;
  length = 0;
  append = 0;
  while (v >= 0) {
    append = max(append, length + out_path[v]);
    length += parent_distance[v];
    v = parent[v];
  }
  tmp += append;
  total = max(total, tmp);

  length = 0;
  v = cycle_start;
  while (v != cycle_end) {
    length += parent_distance[v];
    v = parent[v];
  }
  back = length;

  append = 0;
  v = parent[cycle_start];
  length -= parent_distance[cycle_start];

  while (v != cycle_end) {
    append = max(append, out_path[v] + length);
    length -= parent_distance[v];
    v = parent[v];
  }

  total = max(total, append + dist + max_path_from_node[cycle_start]);

  length = 0;
  v = cycle_start;
  while (v != cycle_end) {
    length = max(length, out_path[v]);
    length -= parent_distance[v];
    append = dist + back + length + out_path[parent[v]];
    total = max(total, append);
    v = parent[v];
  }
  return total;
}

lli calc(int r) {
  parent_distance[r] = 0;
  parent[r] = -1;
  cycle_start = -1;
  cycle_end = -1;
  dist = 0;
  dfs(r);
  return max(max_subtree_path[r], calculate_max_cycle_path());
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  constr_graph(N);
  res = 0;
  for (i = 0; i < N; i++) {
    if (!visited[i]) {
      res += calc(i);
    }
  }
  cout << res << endl;
  return 0;
}