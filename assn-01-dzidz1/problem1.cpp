#include <bits/stdc++.h>
using namespace std;

int N, i;
pair<long long, long long> xy[50005], yx[50005], xMaxMin[50005], yMaxMin[50005];
long long bigRect;

int main() {
  cin >> N;
  for (i = 0; i < N; i++) {
    cin >> xy[i].first >> xy[i].second;
    yx[i].first = xy[i].second;
    yx[i].second = xy[i].first;
  }
  sort(xy, xy + N);
  sort(yx, yx + N);
  bigRect = (xy[N - 1].first - xy[0].first) * (yx[N - 1].first - yx[0].first);
  // 1
  xMaxMin[0].first = xy[0].second;
  xMaxMin[0].second = xy[0].second;
  for (i = 1; i < N; i++) {
    xMaxMin[i].first = max(xMaxMin[i - 1].first, xy[i].second);
    xMaxMin[i].second = min(xMaxMin[i - 1].second, xy[i].second);
  }
  long long rightMax = 0;
  long long rightMin = LLONG_MAX;
  long long leftArea = 0;
  long long rightArea = 0;
  long long result1 = LLONG_MAX;
  for (i = N - 1; i >= 1; i--) {
    rightMax = max(rightMax, xy[i].second);
    rightMin = min(rightMin, xy[i].second);
    if (xy[i].first == xy[i - 1].first)
      continue;
    leftArea = (long long)(xMaxMin[i - 1].first - xMaxMin[i - 1].second) *
               (long long)(xy[i - 1].first - xy[0].first);
    rightArea = (long long)(rightMax - rightMin) *
                (long long)(xy[N - 1].first - xy[i].first);
    result1 = min(result1, (long long)(leftArea + rightArea));
  }

  // 2
  yMaxMin[0].first = yx[0].second;
  yMaxMin[0].second = yx[0].second;
  for (i = 1; i < N; i++) {
    yMaxMin[i].first = max(yMaxMin[i - 1].first, yx[i].second);
    yMaxMin[i].second = min(yMaxMin[i - 1].second, yx[i].second);
  }

  long long upperMax = 0;
  long long upperMin = LLONG_MAX;
  long long upperArea = 0;
  long long lowerArea = 0;
  long long result2 = LLONG_MAX;
  for (i = N - 1; i >= 1; i--) {
    upperMax = max(upperMax, yx[i].second);
    upperMin = min(upperMin, yx[i].second);
    if (yx[i].first == yx[i - 1].first)
      continue;
    upperArea = (long long)(upperMax - upperMin) *
                (long long)(yx[N - 1].first - yx[i].first);
    lowerArea = (long long)(yMaxMin[i - 1].first - yMaxMin[i - 1].second) *
                (long long)(yx[i - 1].first - yx[0].first);
    result2 = min(result2, (long long)(upperArea + lowerArea));
  }

  cout << (long long)(bigRect - min(result1, result2)) << endl;

  return 0;
}