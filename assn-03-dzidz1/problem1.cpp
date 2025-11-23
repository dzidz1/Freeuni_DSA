#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000009;
int m, n, x, ai, bi;
vector<int> a, b;

int solve(int n, int m, int x, vector<int> a, vector<int> b) {
  vector<vector<vector<int>>> dp(
      n + 1, vector<vector<int>>(m + 1, vector<int>(x + 1, 0)));
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      dp[i][j][0] = 1;
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int k = 1; k <= x; k++) {
        if (k > i || k > j)
          continue;
        dp[i][j][k] = dp[i - 1][j][k]; // vixilavt a dan pirvel i - 1 cals
        dp[i][j][k] = (dp[i][j][k] + dp[i][j - 1][k]) %
                      mod; // vixilavt b dan pirvel j - 1 cals
        dp[i][j][k] =
            (dp[i][j][k] - dp[i - 1][j - 1][k]) % mod; // gavcxrilot duplicatebi
        if (a[i - 1] > b[j - 1]) {
          dp[i][j][k] += dp[i - 1][j - 1][k - 1]; // shegvyavs axlandeli wyvili
        }
        dp[i][j][k] = (dp[i][j][k] % mod + mod) % mod;
      }
    }
  }
  return dp[n][m][x];
}

int main() {
  cin >> n >> m >> x;
  for (int i = 0; i < n; i++) {
    cin >> ai;
    a.push_back(ai);
  }
  for (int i = 0; i < m; i++) {
    cin >> bi;
    b.push_back(bi);
  }
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  cout << solve(n, m, x, a, b) << endl;
  return 0;
}