#include <bits/stdc++.h>
using namespace std;
int n,mod;
struct fastmod {
	typedef unsigned long long u64;
	typedef __uint128_t u128;
	int m;
	u64 b;
	fastmod(int m) : m(m), b(((u128)1 << 64) / m) {}
	int reduce(u64 a) {
 		u64 q = ((u128)a * b) >> 64;
		int r = a - q * m;
		return r < m ? r : r - m;
		}
} z(2);
int main() {
	cin >> n >> mod;
 	z = fastmod(mod);
 	cout << 1145141919810ll % mod << ' ' << z.reduce(1145141919810ll) << endl;
}
