#include <bits/stdc++.h>
using namespace std;

int num[50201];
vector<int> primes;

void erathos() {
  for (int i = 2; i * i <= 50201; i++) {
    if (num[i] == 0) {
      for (int j = i * i; j <= 50201; j += i) {
        num[j] = 1;
      }
    }
  }
}

vector<int> getPrimes() {
  vector<int> res;
  for (int i = 2; i <= 50201; i++) {
    if (num[i] == 0)
      res.push_back(i);
  }
  return res;
}

int main() {
  erathos();
  primes = getPrimes();

  int N;
  cin >> N;
  auto nextPrimeIt = upper_bound(primes.begin(), primes.end(), N);
  long long nextPrime = (nextPrimeIt == primes.end()) ? 1 : *nextPrimeIt;

  vector<long long> dp(N + 1, 0);
  dp[0] = 1;

  for (int i = 0; i < primes.size(); i++) {
    for (int j = primes[i]; j <= N; j++) {
      dp[j] += dp[j - primes[i]];
      dp[j] %= nextPrime;
    }
  }

  long long res = dp[N];
  if (find(primes.begin(), primes.end(), N) != primes.end())
    res = res + nextPrime - 1;

  cout << (res % nextPrime) << endl;

  return 0;
}