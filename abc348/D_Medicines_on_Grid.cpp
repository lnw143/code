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
	N = 3e2,
	M = 2e2,
	K = 0,
	Q = 0,
	S = 0,
	P = 998244353// (int)1e9 + 7
;

const vector<pair<int,int>> way {{0,1},{1,0},{0,-1},{-1,0}};

int h,w,n,e[M + 2][M + 2],dis[M + 2][M + 2];
char a[M + 2][M + 2];
void dij() {
	priority_queue<tuple<int,int,int>> hp;
	for(int i=1; i<=h; ++i)
		for(int j=1; j<=w; ++j)
			if(a[i][j]=='S')
				dis[i][j]=e[i][j],
				hp.emplace(e[i][j],i,j);
			else 
				dis[i][j]=-1;
	while(!hp.empty()) {
		const auto [w_,u,v]=hp.top();
		hp.pop();
		if(dis[u][v]!=w_) continue;
		for(const auto& [i,j] : way) {
			int x=u+i,y=v+j;
			if(x<1||y<1||x>h||y>w||a[x][y]=='#') continue;
			if(dis[u][v]-1>dis[x][y]) {
				dis[x][y]=max(e[x][y],dis[u][v]-1);
				hp.emplace(dis[x][y],x,y);
			}
		}
	}
}
void _main() {
	cin>>h>>w;
	for(int i=1; i<=h; ++i)
		cin>>(a[i]+1);
	cin>>n;
	for(int i=1; i<=n; ++i) {
		int r,c,w;
		cin>>r>>c>>w;
		e[r][c]=max(e[r][c],w);
	}
	dij();
	for(int i=1; i<=h; ++i)
		for(int j=1; j<=w; ++j)
			if(a[i][j]=='T') {
				cout<<(dis[i][j]>=0?"Yes":"No");
				break;
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