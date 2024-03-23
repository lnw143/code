#include<cstdio>
#include<cmath>
#include<cstdint>
#include<map>
#include<set>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>
#include<bitset>
#include<random>
#include<chrono>
#include<cassert>
#include<cstdlib>
#include<complex>
#include<deque>
#include<functional>
#include<iostream>
#include<limits>
#include<numeric>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<atcoder/all>

using namespace std;
using namespace atcoder;

using ll = long long;
using db = double;
using ldb = long double;

#define clock() chrono::steady_clock::now()
const auto start_time = clock();
template<typename T = db> T runtime() { return chrono::duration<T>(clock()-start_time).count(); }

const int
	N = 1,
	M = 1,
	K = 1,
	Q = 1,
	S = 1,
	P = 998244353// (int)1e9 + 7
;
using mint = static_modint<P>;

#define MULTITEST 0
const string ss = "wbwbwwbwbwbw";
int n,m;
void solve() {
	scanf("%d%d",&n,&m);
	string str="";
	for(int i=1; i<=100; ++i)
		str+=ss;
	for(int i=0; i<str.size(); ++i) {
		int a=0,b=0,j=i;
		while(j<str.size()&&(a!=n||b!=m)) {
			if(str[j]=='w') ++a;
			else ++b;
			++j;
		}
		if(a==n&&b==m) return printf("Yes"),void();
	}
	printf("No");
}

int main() {
#if MULTITEST
	int T;
	scanf("%d",&T);
	while(T--) solve();
#else
	solve();
#endif
	return 0;
}