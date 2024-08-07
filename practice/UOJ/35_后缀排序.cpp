#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1e5;
int n,sa[N + 2],cnt[N + 2],rk[2][N + 2],ht[N + 2];
char s[N + 2];
struct node {
	int x,y,id;
} p[N + 2],q[N + 2];
bool operator<(const node& a,const node& b) {
	return a.x!=b.x?a.x<b.x:a.y<b.y;
}
bool operator==(const node& a,const node& b) {
	return a.x==b.x&&a.y==b.y;
}
void Sort() {
	memset(cnt,0,sizeof(*cnt)*(n+1));
	for(int i=1; i<=n; ++i) ++cnt[p[i].y];
	for(int i=1; i<=n; ++i) cnt[i]+=cnt[i-1];
	for(int i=n; i>=1; --i) q[cnt[p[i].y]--]=p[i];
	memset(cnt,0,sizeof(*cnt)*(n+1));
	for(int i=1; i<=n; ++i) ++cnt[q[i].x];
	for(int i=1; i<=n; ++i) cnt[i]+=cnt[i-1];
	for(int i=n; i>=1; --i) p[cnt[q[i].x]--]=q[i];
}
int main() {
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1; i<=n; ++i) cnt[s[i]]=1;
	for(int i=1; i<128; ++i) cnt[i]+=cnt[i-1];
	for(int i=1; i<=n; ++i) rk[0][i]=cnt[s[i]];
	for(int j=1,k=1; j<=n; j<<=1,k^=1) {
		for(int i=1; i<=n; ++i) p[i]={rk[k^1][i],i+j<=n?rk[k^1][i+j]:0,i};
		Sort();
		for(int i=1,t=0; i<=n; ++i)	
			if(i>1&&p[i]==p[i-1])
				rk[k][p[i].id]=t;
			else
				rk[k][p[i].id]=++t;
		if((j<<1)>n) swap(rk[k],rk[0]);
	}
	for(int i=1; i<=n; ++i) sa[rk[0][i]]=i;
	for(int i=1; i<=n; ++i) printf("%d ",sa[i]);
	putchar('\n');
	for(int i=1; i<=n; ++i) {
		if(rk[0][i]==1) continue;
		int k=i>1?max(0,ht[rk[0][i-1]]-1):0;
		while(i+k<=n&&sa[rk[0][i]-1]+k<=n&&s[i+k]==s[sa[rk[0][i]-1]+k]) ++k;
		ht[rk[0][i]]=k;
	}
	for(int i=2; i<=n; ++i) printf("%d ",ht[i]);
	return 0;
}