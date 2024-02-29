#include<cstdio>
#define pw2(x) (1<<(x))
using namespace std;
const int N = 30, M = 100, P = 998244353;
using ll = long long;
int n,m,k,i,v[M + 2],ans;
int cnt(int x) {
	int r=0;
	while(x) ++r,x&=x-1;
	return r;
}
void dfs(int x,int s,int sum) {
	if(x>n) {
		if(cnt(s)<=k) ans=(ans+sum)%P;
		return ;
	}
	for(int i=0; i<=m; ++i)
		dfs(x+1,s+(1<<i),(ll)sum*v[i]%P);
}
int main() {
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(i=0; i<=m; ++i)
		scanf("%d",&v[i]);
	dfs(1,0,1);
	printf("%d",ans);
	return 0;
}