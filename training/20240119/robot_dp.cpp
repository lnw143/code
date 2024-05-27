#include<cstdio>
using namespace std;
const int N = 1e4, P = 998244353;
using ll = long long;
ll n;
int q,k,s,t,i,j,f[N + 2];
bool in(int x,int y) {
	do {
		if(y%k==x) return true;
		y/=k;
	} while(y);
	return false;
}
int dp(int s,int t) {
	for(int i=s+1; i<=t; ++i)
		f[i]=0;
	f[s]=1;
	for(int i=s; i<t; ++i)
		for(j=1; j<k; ++j)
			if(in(j,i)||in(j,i+j))
				(f[i+j]+=f[i])%=P;
	return f[t];
}
int main() {
	freopen("robot.in","r",stdin);
	freopen("robot.out","w",stdout);
	scanf("%lld%d%d",&n,&q,&k);
	for(i=1; i<=q; ++i) {
		scanf("%d%d",&s,&t);
		if(k==2) printf("1\n");
		else printf("%d\n",dp(s,t));
	}
	
	return 0;
}