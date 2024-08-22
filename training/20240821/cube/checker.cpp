#include <bits/stdc++.h>

#include "testlib.h"

using ull = unsigned long long;

ull mat[1100];

int main(int argc, char **argv) {
  registerTestlibCmd(argc, argv);
  int n = inf.readInt(), k = inf.readInt();
  for (int i = 1; i <= n; ++i) {
    int a = inf.readInt();
    for (int j = 1; j <= a; ++j) mat[j] |= (1ull << i);
  }
  int qo = ouf.readInt(), qa = ans.readInt();
  if ((qa == -1) && (qo != -1)) quitf(_wa, "No solution but you provide one!");
  if ((qo == -1) && (qa != -1)) quitf(_wa, "There exists solution!");
  if (qo == -1 && qa == -1) quitf(_ok, "Accepted!");
  if (qo > 10000) quitf(_wa, "Too many operations!");
  ull all = (1ull << (n + 1)) - 2;
  mat[0] = all;
  for (int i = 1; i <= qo; ++i) {
    int id = ouf.readInt(1, 2);
    if (id == 1) {
      int x = ouf.readInt(1, n);
      for (int i = 1000; i >= 0; --i) {
        if (mat[i] >> x & 1) {
          if (i + k > 1000) quitf(_wa, "Height exceeds the limit!");
          for (int j = i + 1; j <= i + k; ++j) {
            mat[j] |= (1ull << x);
          }
          break;
        }
      }
    } else {
      int x = ouf.readInt(1, n - k + 1);
      ull now = 0;
      for (int i = x; i <= x + k - 1; ++i) now |= (1ull << i);
      for (int i = 1000; i >= 0; --i) {
        if (mat[i] & now) {
          if (i == 1000) quitf(_wa, "Height exceeds the limit!");
          mat[i + 1] |= now;
          break;
        }
      }
    }
    int delta = 0;
    for (int i = 1; i <= 1000; ++i) {
      if (mat[i] == all)
        ++delta;
      else
        mat[i - delta] = mat[i];
    }
    for (int i = 1000 - delta + 1; i <= 1000; ++i) mat[i] = 0;
  }
  for (int i = 1; i <= 1000; ++i) {
    if (mat[i]) quitf(_wa, "Not empty after operations!");
  }
  quitf(_ok, "Accepted!");
  return 0;
}
