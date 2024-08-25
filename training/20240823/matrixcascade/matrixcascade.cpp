#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
using ll = long long;
const int N = 3e2;
int n;
ll x,y,w,z;
bool bz[N + 2][N + 2];
bool check(ll x,ll y,ll w,ll z) {
	if(x>y) swap(x,y);
	if(z<y-x) return false;
	z-=y-x;
	y=x;
	if(z&1) return false;
	if(x+y<z) return false;
	if(x+y-z>w*2) return false;
	return true;
}
namespace fenwick {
	int s[N + 2][N + 2];
	void add(int x,int y,int v) {
		for(int i=x; i<=n; i+=i&-i)
			for(int j=y; j<=n; j+=j&-j)
				s[i][j]+=v;
	}
	int sum(int x,int y) {
		int r=0;
		for(int i=x; i; i&=i-1)
			for(int j=y; j; j&=j-1)
				r+=s[i][j];
		return r;
	}
	void clean() {
		memset(s,0,sizeof(s));
	}
}
bool ok(int u,int v) {
	if(bz[u][v]) return false;
	
}
int main() {
	freopen("matrixcascade.in","r",stdin);
	freopen("matrixcascade.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--) {
		scanf("%d%lld%lld",&n,&x,&y);
		w=z=0;
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=n; ++j)
				w+=i*j-1,
				z+=(i-1)*(n-j);
		if(check(x,y,w,z))
			printf("YES\n");
		else {
			printf("NO\n");
			continue;
		}
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=n; ++j)
				bz[i][j]=false;
		for(int i=1; i<=n*n; ++i) {
			for(int u=1; u<=n; ++u)
				for(int v=1; v<=n; ++v)
					if(ok(u,v)) {
						bz[u][v]=true;

					}
		}
		fenwick::clean();
	}
	return 0;
}