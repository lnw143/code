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
#include<iomanip>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#define pbk push_back
#define ebk emplace_back
#define mkp make_pair
#define endl '\n'

using namespace std;

using ll = long long;
using llu = long long unsigned;
using db = double;
using ldb = long double;
template<typename T> using heap = priority_queue<T,vector<T>,greater<T>>;

#define clock() chrono::steady_clock::now()
const auto start_time = clock();
template<typename T = db> T runtime() { return chrono::duration<T>(clock()-start_time).count(); }

mt19937 rnd(random_device{}());
ll randint(ll l,ll r) {
	return uniform_int_distribution<ll>(l,r)(rnd);
}
db randpr(db l=0,db r=1) {
	return uniform_real_distribution<db>(l,r)(rnd);
}

// #define MULTITEST
#define FILENAME "a"

const int
	N = 1e5,
	M = 1,
	K = 1,
	Q = 1,
	S = 1,
	P = 998244353// (int)1e9 + 7
;

int n,a[N + 2],pre[N + 2],nxt[N + 2],cnt[3];
void _main() {
	cin>>n;
	for(int i=1; i<=n; ++i)
		cin>>a[i];
	if(a[1]==a[n]) return cout<<"no",void();
	for(int i=1; i<n; ++i)
		if(a[i]==a[i+1])
			return cout<<"no",void();
	set<int> st;
	for(int i=1; i<=n; ++i)
		st.emplace(a[i]),++cnt[a[i]];
	if(st.size()<3)
		return cout<<"no",void();
	pre[1]=n;
	nxt[n]=1;
	for(int i=1; i<n; ++i)
		pre[i+1]=i,nxt[i]=i+1;
	int u=1,m=n;
	cout<<"yes\n";
	while(m>3) {
		if(cnt[a[u]]>1&&a[pre[u]]!=a[nxt[u]]) {
			cout<<pre[u]<<' '<<nxt[u]<<endl;
			nxt[pre[u]]=nxt[u];
			pre[nxt[u]]=pre[u];
			--cnt[a[u]];
			--m;
		}
		u=nxt[u];
	}
	return ;
}

int main() {
#if defined(FILENAME) && !defined(CPH)
	freopen(FILENAME".in","r",stdin);
	freopen(FILENAME".out","w",stdout);
#endif
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	cout<<fixed<<setprecision(15);
	int T=1;
#if defined(MULTITEST)
	cin>>T;
#endif
	while(T--) _main();
	return 0;
}