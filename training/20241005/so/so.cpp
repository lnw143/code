#include <cstdio>
using namespace std;
using ll = long long;
using LL = __int128_t;
const int M = 14;
ll n;
LL ans;
int m;
ll s[M + 2];
LL exgcd(LL a,LL b,LL &x,LL &y) {
	if(!b) {
		x=1,y=0;
		return a;
	}
	LL d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
LL gcd(LL a,LL b) {
	return b?gcd(b,a%b):a;
}
void dfs(int u,LL a,LL b,int t) {
	if(a>n||b>n||gcd(a,b)>1) return ;
	if(u>m) {
		if(a==1||b==1) return ;
		LL x,y;
		LL d=exgcd(a,b,x,y);
		LL r=(a*x%(a*b)+a*b)%(a*b);
		if(r>n) return ;
		if(t) ans-=(n-r)/(a*b)+1;
		else ans+=(n-r)/(a*b)+1;
		return ;
	}
	dfs(u+1,a,b,t);
	dfs(u+1,a/gcd(a,s[u])*s[u],b,t^1);
	dfs(u+1,a,b/gcd(b,s[u])*s[u],t^1);
}
int main() {
	freopen("so.in","r",stdin);
	freopen("so.out","w",stdout);
	scanf("%lld%d",&n,&m);
	if(m==0) return printf("0"),0;
	for(int i=1; i<=m; ++i) {
		scanf("%lld",&s[i]);
		if(s[i]==1) return printf("%lld",n),0;
	}
	--n;
	dfs(1,1,1,0);
	for(int i=1; i<=m; ++i)
		if(n%s[i]==0) {
			++ans;
			break;
		}
	printf("%lld",ll(ans));
	return 0;
}