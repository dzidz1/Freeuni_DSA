#include <bits/stdc++.h>
using namespace std;

#define MAX_SIZE 500010

struct node {
  int sum;
  int prefix;
  int sufix;
};

int n, m, type, p, a, b, ans, length, lazy[MAX_SIZE * 4] = {-1};
node segment_tree[MAX_SIZE * 4];

void apply_lazy(int curr_idx, int curr_start, int curr_end) {

  if (lazy[curr_idx] != -1) { // ar aris update sachiro
    if (lazy[curr_idx] == 1) {
      segment_tree[curr_idx].sufix = 0;
      segment_tree[curr_idx].prefix = 0;
      segment_tree[curr_idx].sum = 0;
    } else {
      segment_tree[curr_idx].sufix = (curr_end - curr_start + 1);
      segment_tree[curr_idx].prefix = (curr_end - curr_start + 1);
      segment_tree[curr_idx].sum = (curr_end - curr_start + 1);
    }

    if (curr_start != curr_end) { // shvilebze gavrceleba
      lazy[curr_idx * 2] = lazy[curr_idx];
      lazy[curr_idx * 2 + 1] = lazy[curr_idx];
    }
    lazy[curr_idx] = -1; // gasuftaveba wina mnishvnelobis
  }
}

void update_helper(int curr_idx, int curr_start, int curr_end, int query_start,
                   int query_end, bool to_one) {
  apply_lazy(curr_idx, curr_start, curr_end);

  if (curr_start > curr_end || curr_start > query_end || curr_end < query_start)
    return;

  if (curr_start >= query_start && curr_end <= query_end) {
    lazy[curr_idx] = to_one ? 1 : 0;
    apply_lazy(curr_idx, curr_start, curr_end);
    return;
  }

  int mid = (curr_start + curr_end) / 2;
  update_helper(curr_idx * 2, curr_start, mid, query_start, query_end, to_one);
  update_helper(curr_idx * 2 + 1, mid + 1, curr_end, query_start, query_end,
                to_one);

  segment_tree[curr_idx].sum =
      max({segment_tree[curr_idx * 2].sum, segment_tree[curr_idx * 2 + 1].sum,
           segment_tree[curr_idx * 2].sufix +
               segment_tree[curr_idx * 2 + 1].prefix});
  segment_tree[curr_idx].prefix = segment_tree[curr_idx * 2].prefix;
  if (segment_tree[curr_idx * 2].prefix == mid - curr_start + 1) {
    segment_tree[curr_idx].prefix += segment_tree[curr_idx * 2 + 1].prefix;
  }
  segment_tree[curr_idx].sufix = segment_tree[curr_idx * 2 + 1].sufix;
  if (segment_tree[curr_idx * 2 + 1].sufix == curr_end - mid) {
    segment_tree[curr_idx].sufix += segment_tree[curr_idx * 2].sufix;
  }
}

void update_range(int query_start, int query_end, bool to_one) {
  update_helper(1, 1, n, query_start, query_end, to_one);
}

int get_idx(int curr_start, int curr_end, int curr_idx, int length) {
  apply_lazy(curr_idx, curr_start, curr_end);

  if (curr_start == curr_end) {
    return curr_start;
  }
  if (length > segment_tree[curr_idx].sum)
    return 0;
  int mid = (curr_start + curr_end) / 2;
  apply_lazy(curr_idx * 2, curr_start, mid);
  apply_lazy(curr_idx * 2 + 1, mid + 1, curr_end);
  if (segment_tree[curr_idx * 2].sum >= length) {
    return get_idx(curr_start, mid, curr_idx * 2, length);
  }
  if (segment_tree[curr_idx * 2].sufix +
          segment_tree[curr_idx * 2 + 1].prefix >=
      length) {
    return mid - segment_tree[curr_idx * 2].sufix + 1;
  }
  return get_idx(mid + 1, curr_end, curr_idx * 2 + 1, length);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  update_range(1, n, false);
  for (int i = 0; i < m; i++) {
    cin >> type;
    if (type == 1) {
      cin >> length;
      ans = get_idx(1, n, 1, length);
      cout << ans << endl;
      if (ans != 0) {
        update_range(ans, ans + length - 1, true);
      }
    } else if (type == 2) {
      cin >> a >> b;
      update_range(a, a + b - 1, false);
    }
  }

  return 0;
}