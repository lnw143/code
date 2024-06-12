#include <cstdio>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;
using ll = long long;
const int N = 1e3, K = 15, S = 1 << K, T = 3, P = 1e9 + 7;
const char sig[] = "NOI";
int n,k;
char s[K + 2];
int f[2][S + 2][T + 2],ans[K + 2];
bool bz[S + 2][T + 2];
int p[S + 2][T + 2];
int trans(int sta,int c) {
	if(bz[sta][c]) return p[sta][c];
	bz[sta][c]=true;
	static int a[K + 2],b[K + 2];
	for(int i=0; i<k; ++i)
		a[i+1]=a[i]+!!(sta&(1<<i));
	for(int i=1; i<=k; ++i)
		b[i]=max({b[i-1],a[i],a[i-1]+(s[i]==sig[c])});
	int res=0;
	for(int i=0; i<k; ++i)
		if(b[i]<b[i+1])
			res|=1<<i;
	return p[sta][c]=res;
}
int popcnt(int x) {
	return x?popcnt(x&(x-1))+1:0;
}
int main() {
	scanf("%d%d%s",&n,&k,s+1);
	f[0][0][0]=1;
	for(int i=1; i<=n; ++i) {
		memset(f[i&1],0,sizeof(f[i&1]));
		for(int j=0; j<(1<<k); ++j)
			for(int t=0; t<T; ++t)
				for(int c=0; c<T; ++c)
					(f[i&1][trans(j,c)][t==c?t+1:(c==0)]+=f[(i&1)^1][j][t])%=P;
	}
	for(int i=0; i<(1<<k); ++i)
		for(int j=0; j<T; ++j)
			(ans[popcnt(i)]+=f[n&1][i][j])%=P;
	for(int i=0; i<=k; ++i)
		printf("%d\n",ans[i]);
	return 0;
}