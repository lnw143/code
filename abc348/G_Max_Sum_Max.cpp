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
// #define FILENAME "a"

const int
	N = 2e5,
	M = 0,
	K = 0,
	Q = 0,
	S = 0,
	P = 998244353// (int)1e9 + 7
;

int n,v[N + 2];
pair<ll,int> a[N + 2];
void _main() {
	cin>>n;
	for(int i=1; i<=n; ++i) {
		cin>>a[i].second>>a[i].first;
		v[i]=a[i].second;
	}
	sort(a+1,a+n+1);
	sort(v+1,v+n+1);
	int k=1;
	for(int i=2; i<=n; ++i)
		if(a[i].second-a[i].first>a[k].second-a[k].first)
			k=i;
	ll ans=a[k].second-a[k].first;
	cout<<ans<<endl;
	priority_queue<int> hp;
	set<pair<ll,int>> st;
	for(int i=1; i<k; ++i)
		hp.emplace(a[i].second);
	for(int i=k+1; i<=n; ++i)
		st.emplace(a[i].second-a[i].first,i);
	for(int i=2; i<=n; ++i) {
		assert(hp.size()+st.size()==n-i+1);
		if(!st.empty()&&(hp.empty()||(*st.begin()).first+a[k].first>=hp.top())) {
			int k_=k;
			auto [val,pos]=*st.rbegin();
			st.erase(*st.rbegin());
			ans+=val+a[k].first;
			k=pos;
			for(int i=k_+1; i<k; ++i)
				st.erase(mkp(a[i].second-a[i].first,i)),
				hp.emplace(a[i].second);
			cout<<ans<<endl;
		} else {
			ans+=hp.top();
			hp.pop();
			cout<<ans<<endl;
		}
	}
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