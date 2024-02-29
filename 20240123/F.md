便宜起见，我们考虑将给定的序列重复连接两次，形成新的序列

$$
C' = (C'_1, C'_2, \ldots, C'_{2N}) \coloneqq (C_1, C_2, \ldots, C_{N}, C_1, C_2, \ldots, C_{N})
$$

并将问题转化为对序列 $C'$ 的区间 $[l, l+N-1]$ 进行操作，在箱子中放入球的总数。对于每个 $l = 1, 2, \ldots, N$，我们需要求得该问题的答案。我们用 $f(c, l, r)$ 表示序列 $C'$ 的区间 $[l, r]$ 中颜色为 $c$ 的球的个数，并用 $g(c)$ 表示原始序列 $C$ 中颜色 $c$ 的球的个数。

首先，我们考虑对于固定的区间 $[l, l+N-1]$ 求解问题的答案。假设在区间 $[l, l+N-1]$ 进行操作后，某一颜色 $c$ 的球使用的箱子数量为 $b(c, l)$，则颜色为 $c$ 的球最终放入箱子中的总数为 $\min\lbrace b(c, l) \times K, g(c)\rbrace$，而答案 $\mathrm{ans}_l$ 可以表示为

$$
\mathrm{ans}_l = \sum_{c = 1}^N \min\lbrace b(c, l) \times K, g(c)\rbrace
$$

对于每个颜色 $c$，如果知道了 $b(c, l)$，那么就可以求得 $\mathrm{ans}_l$。因此，接下来我们考虑如何求解 $b(c, l)$。

能够放入空箱子中的球（从而使得该颜色使用的箱子数量增加 $1$）是该颜色的球中的第 $1, K+1, 2K+1, 3K+1, \ldots$ 个球。因此，在每个颜色中，我们将第 $1, K+1, 2K+1, 3K+1, \ldots$ 个球称为**机会球**。

每当一个机会球（无论颜色如何）被处理时，空箱子的数量减少 $1$，所以 $b(c, l)$ 等于前 $M$ 个机会球中颜色为 $c$ 的机会球的数量。那么，第 $M$ 个机会球的位置在哪里呢？

当从位置 $l$ 开始操作时，区间 $[l, r]$ 中颜色为 $c$ 的机会球的数量是 $\left\lceil f(c, l, r) / K \right\rceil$，因此区间 $[l, r]$ 中的机会球的总数（无论颜色如何）可以表示为

$$
S(l, r) \coloneqq \sum_{c = 1}^N \left\lceil \frac{f(c, l, r)}{K} \right\rceil
$$

因此，第 $M$ 个机会球的位置可以通过找到最小的 $r$ 满足 $S(l, r) \geq M$ 来确定。记作 $r_l$，则 $b(c, l) = \left\lceil f(c, l, r_l) / K \right\rceil$，因此答案 $\mathrm{ans}_l$ 可以表示为

$$
\mathrm{ans}_l = \sum_{c = 1}^N \min\left\lbrace \left\lceil \frac{f(c, l, r_l)}{K} \right\rceil \times K, g(c) \right\rbrace \tag{1} 
$$

（特别地，如果在范围 $r \leq l+N-1$ 中找不到满足 $S(l, r) \geq M$ 的最小 $r$，那么我们约定 $r_l \coloneqq l+N-1$）。换句话说，要求得 $\mathrm{ans}_l$，我们需要找到 $r_l$ 并计算上述公式（1）。然而，对于所有的 $l = 1, 2, \ldots, N$ 来做这一操作是不现实的，因为这样的话无法在可接受的时间内完成。

因此，我们注意到根据上述讨论得出 $r_1 \leq r_2 \leq \cdots \leq r_N$，并决定按顺序对 $l = 1, 2, \ldots, N$ 求解答案。通过使用所谓的**尺取法**，我们可以在增加 $l$ 的同时有效地获取每个 $r_l$。在尺取法的过程中，我们维护当前正在看的区间 $[l', r']$ 中与公式（1）相对应的值，并在每次增减 $l'$ 或 $r'$ 时即时更新这些值，从而可以在 $O(N)$ 的时间内求得每个 $\mathrm{ans}_l$。

下面是使用 C++ 语言编写的解答示例：

```cpp
#include <iostream>
using namespace std;

int n, m, k;
int c[400001], all[200001];
int cnt[200001], box[200001], sum, ans;

void add(int i,int x){
	ans -= min(box[i] * k, all[i]);
	sum -= box[i];
	box[i] -= (cnt[i]+k-1)/k;
	cnt[i] += x;
	box[i] += (cnt[i]+k-1)/k;
	sum += box[i];
	ans += min(box[i] * k, all[i]);
}

int main(void){
  cin >> n >> m >> k;
  for(int i = 1; i <= n; i++) cin >> c[i], c[n+i] = c[i], all[c[i]]++;

  int r = 0;
  for(int l = 1; l <= n; l++){
    while(r+1 < l+n && sum < m) r++, add(c[r], 1);
    cout << ans << "\n";
    add(c[l], -1);
  }

  return 0;
}
```

请注意，这是一个 C++ 语言的示例代码。