#include <bits/stdc++.h>
using namespace std;

int n, m, p_i, orders[40010], dp[40010], i, cnt, diff;
long long res;
set<pair<int, int>> type_idx;
set<pair<int, int>> idx_type;

int main() {
  cin >> n >> m;
  for (i = 1; i <= n; i++) {
    cin >> p_i;
    orders[i] = p_i;
  }

  dp[1] = 1;
  type_idx.insert({orders[1], 1});
  idx_type.insert({1, orders[1]});

  for (i = 2; i <= n; i++) {
    dp[i] = dp[i - 1];
    if (orders[i] != orders[i - 1]) {
      dp[i]++;
    } else {
      continue;
    }

    auto it = type_idx.lower_bound({orders[i], 0});
    if (it != type_idx.end() && it->first == orders[i]) {
      type_idx.erase(it);
      idx_type.erase({it->second, it->first});
    }

    idx_type.insert({i, orders[i]});
    type_idx.insert({orders[i], i});

    cnt = 201;
    diff = 0;

    auto it1 = idx_type.rbegin();
    while (it1 != idx_type.rend() && cnt != 0) {
      if (it1->second != orders[i]) {
        diff++;
        dp[i] = min(dp[i], dp[it1->first] + diff * diff);
        cnt--;
      }
      it1++;
    }
  }

  cout << dp[n] << endl;

  return 0;
}