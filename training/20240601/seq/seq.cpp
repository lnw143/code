#include <cstdio>
#include <random>
#include <chrono>
#include <vector>
#include <cstring>
#include <map>
#define hash asidfbsxjaiuf
using namespace std;
const int N = 70, K = 3, P = 1e9 + 7;
using ll = long long;
int n,m,a[N + 2];

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int randint(int l,int r) {
	return uniform_int_distribution<int>(l,r)(rnd);
}

struct hash {
	int v[K + 2];
	int& operator [](int x) { return v[x]; }
	const int& operator [](int x) const { return v[x]; }
};

bool operator<(const hash& a,const hash& b) {
	for(int i=0; i<K; ++i)
		if(a[i]!=b[i])
			return a[i]<b[i];
	return false;
}

struct hasher {
	int A[K + 2],B[K + 2];
	hash make(int l,int r) {
		hash res;
		for(int i=0; i<K; ++i) {
			res[i]=0;
			for(int j=l; j<=r; ++j)
				res[i]=((ll)res[i]*A[i]+a[j])%B[i];
		}
		return res;
	}
	hasher() {
		for(int i=0; i<K; ++i)
			A[i]=randint(100,1000),
			B[i]=randint(1e9,2e9);
	}
} fp;

map<hash,vector<int>> mp[N + 2];

namespace dp {
	ll f[N + 2][N + 2],g[N + 2][N + 2];
	void init() {
		memset(f,0,sizeof(f));
		for(int i=1; i<=n; ++i)
			for(int j=i-1; j<=n; ++j)
				f[i][j]=1;
	}
	void solve() {
		memcpy(g,f,sizeof(f));
		for(int i=1; i<=n; ++i)
			(--g[i][i])%=P;
		for(int i=0; i<n; ++i) {
			for(int j=1; j<=n-i; ++j)
				(g[j][j+i]+=g[j+1][j+i]+g[j][j+i-1]-g[j+1][j+i-1])%=P;
			for(const auto& [h,p] : mp[i])
				for(int j=0; j<p.size()-1; ++j)
					(g[p[j]][p[j+1]+i]-=g[p[j]][p[j]+i])%=P;
		}
		memcpy(f,g,sizeof(g));
	}
}

int main() {
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	for(int i=0; i<n; ++i) {
		for(int j=1; j<=n-i; ++j)
			mp[i][fp.make(j,j+i)].emplace_back(j);
		// printf("%d :\n",i+1);
		// for(const auto& [h,p] : mp[i]) {
		// 	for(auto j : p)
		// 		printf("%d ",j);
		// 	putchar('\n');
		// }
	}
	dp::init();
	for(int i=1; i<m; ++i)
		dp::solve();
	printf("%lld",(dp::f[1][n]%P+P)%P);
	return 0;
}