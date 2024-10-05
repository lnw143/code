#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 2e3;
int n,p[N + 2],pos[N + 2],q[N + 2];
int ans=1e9;
int move(int i,int j) {
	if(i==j) return 0;
	int tmp=q[i];
	for(int k=i; k<j; ++k) q[k]=q[k+1];
	for(int k=i; k>j; --k) q[k]=q[k-1];
	q[j]=tmp;
	return i+j;
}
int find(int v) {
	int k=1;
	for(; q[k]!=v; ++k);
	return k;
}
int solve(int s,int v) {
	int b=0;
	for(int i=1; i<v; ++i)
		if((s>>(i-1))&1)
			b=i;
	if(!b) return move(find(v),1);
	int from=find(v),to=find(b);
	return from<to?move(from,to):move(from,to+1);
}
int main() {
	freopen("strong.in","r",stdin);
	freopen("strong.out","w",stdout);
	scanf("%d",&n);
	if(n>20) {
		ans=0;
		for(int i=2; i<=n; i+=2)
			ans+=2*i-1;
		printf("%d",ans);
		return 0;
	}
	for(int i=1; i<=n; ++i)
		scanf("%d",&p[i]),p[i]=n-p[i]+1,pos[p[i]]=i;
	for(int i=0; i<(1<<n); ++i) {
		int lst=0;
		bool ok=true;
		for(int j=1; j<=n; ++j)
			if((i>>(j-1))&1) {
				if(pos[j]<lst) {
					ok=false;
					break;
				}
				lst=pos[j];
			}
		if(!ok) continue;
		for(int j=1; j<=n; ++j) q[j]=p[j];
		int sum=0;
		for(int j=n; j>=1; --j)
			if(!((i>>(j-1))&1))
				sum+=solve(i,j);
		ans=min(ans,sum);
	}
	printf("%d",ans);
	return 0;
}