#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
using ll = long long;
const int N = 5e5;
int n,rk[2][N + 2],sa[N + 2],ht[N + 2],stk[N + 2],pre[N + 2],nxt[N + 2],tp;
char s[N + 2];
struct node {
	int x,y,id;
} a[N + 2];
bool operator<(const node &a,const node &b) { return a.x!=b.x?a.x<b.x:a.y<b.y; }
int main() {
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1; i<=n; ++i)
		rk[0][i]=s[i];
	int k=1;
	for(int j=1; j<n; j<<=1,k^=1) {
		for(int i=1; i<=n; ++i)
			a[i]=node{rk[k^1][i],i+j<=n?rk[k^1][i+j]:0,i};
		sort(a+1,a+n+1);
		for(int i=1,p=0; i<=n; ++i)
			if(i!=1&&a[i].x==a[i-1].x&&a[i].y==a[i-1].y)
				rk[k][a[i].id]=p;
			else 
				rk[k][a[i].id]=++p;
	}
	if(!k) swap(rk[0],rk[1]);
	for(int i=1; i<=n; ++i)
		sa[rk[0][i]]=i;
	for(int i=1,p=0; i<=n; ++i) {
		p&&--p;
		if(rk[0][i]==1) continue;
		int j=sa[rk[0][i]-1];
		while(j+p<=n&&i+p<=n&&s[i+p]==s[j+p]) ++p;
		ht[rk[0][i]]=p;
	}
	for(int i=1; i<=n; ++i) {
		while(tp>0&&ht[stk[tp]]>ht[i]) nxt[stk[tp--]]=i;
		if(tp>0) pre[i]=stk[tp];
		else pre[i]=1;
		stk[++tp]=i;
	}
	while(tp>0) nxt[stk[tp--]]=n+1;
	ll ans=n*(n-1ll)*(n+1)/2;
	for(int i=1; i<=n; ++i)
		ans-=2ll*(i-pre[i])*(nxt[i]-i)*ht[i];
	printf("%lld",ans);
	return 0;
}