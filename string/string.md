## 题目背景

$\tt“unbelievable,uncountable,unforgettable,unstoppable...”$

$\tt“This\ problem\ is\ \textbf{unsolvable}.”$

## 题目描述

给定 $N$ 个字符串，求出它们两两之间的最长公共前缀（$\tt LCP$）的长度与最长公共后缀（$\tt LCS$）的长度的积之和模 $10^9 +7$ 的值。

形式化地，$\tt LCP$ 与 $\tt LCS$ 定义如下：

$$
\text{LCP}(S,T)=\max{ \{ k\ |\ S[1,k] = T[1,k] \} }
$$

$$
\text{LCS}(S,T)=\max{ \{ k\ |\ S[|S|-k+1,|S|] = T[|T|-k+1,|T|] \} }
$$

其中，

- $|S|$ 表示字符串 $S$ 的长度。
- $S[l,r]$ 表示字符串 $S$ 第 $l$ 位到第 $r$ 位形成的子串（字符串下标以 $1$ 开始）。
- 特别地，当 $l > r$ 时，$S[l,r] = \emptyset$。

请你求出

$$
\sum _{i=1} ^{N-1} \sum _{j=i+1} ^N \text{LCP}(S_i,S_j) \times \text{LCS}(S_i,S_j)\ \text{mod}\ (10^9+7)
$$

## 输入格式

第一行一个正整数 $N$。

接下来 $N$ 行，每行一个由小写字母构成的字符串 $S_i$。

## 输出格式

输出一行一个整数，表示所求的值。

## 样例 #1

### 样例输入 #1

```
2
abcdcba
abba
```

### 样例输出 #1

```
4
```

## 样例 #2

```
见下发文件下string/string1.in与string/string1.out。
```

## 样例 #3

```
见下发文件下string/string2.in与string/string2.out。
```

## 数据范围与约定

数据采用捆绑测试。

对于所有数据，均保证 $\sum |S_i| \le 5 \times 10^5$。

| Subtask编号 | 分数 | 约定 |
| ----------- | ---- | ---- |
| 0 | 10 | $\sum |S_i| \le 10^3$ |
| 1 | 30 | $N \le 10^3$ |
| 2 | 60 | 无其他特殊约定 |

