#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
using ull = unsigned long long;
const int N = 1e3, Base = 131;
int n,m,k;
char c[N + 2][N + 2];
vector<int> ans;
bool vis[N + 2][N + 2];
ull hs;
bool dfs(int x,int y) {
	if(y>m) ++x,y=1;
	if(x>n) return true;
	if(vis[x][y]) return dfs(x,y+1);
	if(y+k-1<=m) {
		bool f=false;
		ull s=0;
		for(int i=0; i<k; ++i)
			if(vis[x][y+i]) {
				f=true;
				break;
			} else 
				s=s*Base+c[x][y+i];
		if(!f&&s==hs) {
			for(int i=0; i<k; ++i) vis[x][y+i]=true;
			if(dfs(x,y+1)) return true;
			for(int i=0; i<k; ++i) vis[x][y+i]=false;
			return false;
		}
	}
	if(x+k-1<=n) {
		bool f=false;
		ull s=0;
		for(int i=0; i<k; ++i)
			if(vis[x+i][y]) {
				f=true;
				break;
			} else
				s=s*Base+c[x+i][y];
		if(!f&&s==hs) {
			for(int i=0; i<k; ++i) vis[x+i][y]=true;
			if(dfs(x,y+1)) return true;
			for(int i=0; i<k; ++i) vis[x+i][y]=false;
			return false;
		}
	}
	return false;
}
bool check() {
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			vis[i][j]=false;
	if(k<=m) {
		hs=0; for(int i=1; i<=k; ++i) hs=hs*Base+c[1][i];
		if(dfs(1,1)) return true;
	}
	if(k<=n) {
		hs=0; for(int i=1; i<=k; ++i) hs=hs*Base+c[i][1];
		if(dfs(1,1)) return true;
	}
	return false;
}
int main() {
	freopen("giovanni.in","r",stdin);
	freopen("giovanni.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%s",c[i]+1);
	for(k=1; k<=n||k<=m; ++k)
		if((n%k==0||m%k==0)&&check())
			ans.push_back(k);
	printf("%d\n",ans.size());
	for(auto i : ans)
		printf("%d ",i);
	return 0;
} 