#include <iostream>
using namespace std;

#define MAX_SIZE 1000010

int segment_tree[MAX_SIZE * 4], lazy[MAX_SIZE * 4], arr[MAX_SIZE], n, k, type,
    l, r;

void update_helper(int curr_idx, int curr_start, int curr_end, int query_start,
                   int query_end) {
  if (lazy[curr_idx] != 0) {
    segment_tree[curr_idx] =
        (curr_end - curr_start + 1) - segment_tree[curr_idx];
    if (curr_start != curr_end) {
      lazy[curr_idx * 2] ^= 1;
      lazy[curr_idx * 2 + 1] ^= 1;
    }
    lazy[curr_idx] = 0;
  }

  if (curr_start > curr_end || curr_start > query_end || curr_end < query_start)
    return;

  if (curr_start >= query_start && curr_end <= query_end) {
    segment_tree[curr_idx] =
        (curr_end - curr_start + 1) - segment_tree[curr_idx];
    if (curr_start != curr_end) {
      lazy[curr_idx * 2] ^= 1;
      lazy[curr_idx * 2 + 1] ^= 1;
    }
    return;
  }

  int mid = (curr_start + curr_end) / 2;
  update_helper(curr_idx * 2, curr_start, mid, query_start, query_end);
  update_helper(curr_idx * 2 + 1, mid + 1, curr_end, query_start, query_end);
  segment_tree[curr_idx] =
      segment_tree[curr_idx * 2] + segment_tree[curr_idx * 2 + 1];
}

void update_range(int n, int query_start, int query_end) {
  update_helper(1, 1, n, query_start, query_end);
}

int get_sum_helper(int curr_start, int curr_end, int query_start, int query_end,
                   int curr_idx) {
  if (lazy[curr_idx] != 0) {
    segment_tree[curr_idx] =
        (curr_end - curr_start + 1) - segment_tree[curr_idx];
    if (curr_start != curr_end) {
      lazy[curr_idx * 2] ^= 1;
      lazy[curr_idx * 2 + 1] ^= 1;
    }
    lazy[curr_idx] = 0;
  }

  if (curr_start > curr_end || curr_start > query_end || curr_end < query_start)
    return 0;

  if (curr_start >= query_start && curr_end <= query_end)
    return segment_tree[curr_idx];

  int mid = (curr_start + curr_end) / 2;
  return get_sum_helper(curr_start, mid, query_start, query_end, curr_idx * 2) +
         get_sum_helper(mid + 1, curr_end, query_start, query_end,
                        curr_idx * 2 + 1);
}

int get_sum(int n, int query_start, int query_end) {
  if (query_start < 1 || query_end > n || query_start > query_end) {
    cout << "Error!" << endl;
    return -1;
  }
  return get_sum_helper(1, n, query_start, query_end, 1);
}

void construct_helper(int arr[], int curr_start, int curr_end, int curr_idx) {
  if (curr_start > curr_end)
    return;

  if (curr_start == curr_end) {
    segment_tree[curr_idx] = arr[curr_start];
    return;
  }

  int mid = (curr_start + curr_end) / 2;
  construct_helper(arr, curr_start, mid, curr_idx * 2);
  construct_helper(arr, mid + 1, curr_end, curr_idx * 2 + 1);
  segment_tree[curr_idx] =
      segment_tree[curr_idx * 2] + segment_tree[curr_idx * 2 + 1];
}

void construct(int arr[], int n) { construct_helper(arr, 1, n, 1); }

int main() {
  cin >> n >> k;

  construct(arr, n);

  for (int i = 0; i < k; i++) {
    cin >> type >> l >> r;
    if (type == 0) {
      update_range(n, l, r);
    } else {
      cout << get_sum(n, l, r) << endl;
    }
  }

  return 0;
}