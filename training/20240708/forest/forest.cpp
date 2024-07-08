#include <cstdio>
#include <vector>
using namespace std;
const int N = 2e3, M = 12;
using ll = long long;
template<int S> struct tree {
	int n;
	vector<int> e[S + 2];
	void init() {
		scanf("%d",&n);
		for(int i=1; i<n; ++i) {
			int x,y;
			scanf("%d%d",&x,&y);
			e[x].push_back(y);
			e[y].push_back(x);
		}
	}
	bool is_chain() {
		for(int i=1; i<=n; ++i)
			if(e[i].size()>2)
				return false;
		return true;
	}
	bool is_flower() {
		int s=0;
		for(int i=1; i<=n; ++i)
			if(e[i].size()>1)
				++s;
		return s<=1;
	}
};
tree<N> s;
tree<M> t;
int P;
ll c[N + 2][M + 2];
void init_binom(int n,int m) {
	for(int i=0; i<=n; ++i) c[i][0]=1;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=i&&j<=m; ++j)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%P;
}
int main() {
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
	s.init();
	t.init();
	scanf("%d",&P);
	// if(t.is_chain()) {

	// } else 
	if(t.is_flower()) {
		int ans=0;
		if(t.n==2) {
			ans+=s.e[1].size();
			for(int i=2; i<=s.n; ++i)	
				ans+=s.e[i].size()-1;
		} else {
			init_binom(s.n,t.n);
			for(int i=1; i<=s.n; ++i)
				(ans+=c[s.e[i].size()][t.n-1])%=P;
		}
		printf("%d",ans);
	}
	return 0;
}