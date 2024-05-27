#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 5e5, K = 10, P = 1e9 + 7;
int n,m,i,w[K + 2],c[N + 2],d[N + 2],a[K + 2],b[K + 2],mx[K + 2],mn[K + 2],ans;
namespace Subtask0 {
	void ck() {
		for(int i=1; i<=m; ++i)
			b[i]=a[i];
		int i=1,s=0;
		while(true) {
			b[c[i]]+=d[i];
			++ans%=P;
			++s;
			if(b[c[i]]>w[c[i]]||b[c[i]]<1) break;
			i=i%n+1;
		}
	}
	void dfs(int x) {
		if(x>m) {
			ck();
			return ;
		}
		for(int i=1; i<=w[x]; ++i) {
			a[x]=i;
			dfs(x+1);
		}
	}
	int main() {
		dfs(1);
		printf("%d",ans);
		return 0;
	}
}
namespace Subtask1 {
	int f[N + 2],g[N + 2];
	int main() {
		int s=0;
		for(i=1; i<=w[1]; ++i)
			f[i]=g[i]=1<<30;
		for(i=1; i<=n; ++i) {
			s+=d[i];
			if(s<0)
				g[-s]=min(g[-s],i);
			else
				f[s]=min(f[s],i);
		}
		for(i=1; i<=w[1]; ++i)
			ans=(ans+min(g[i],f[w[1]-i+1]))%P;
		printf("%d",ans);
		return 0;
	}
}

int main() {
	freopen("walk.in","r",stdin);
	freopen("walk.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1; i<=m; ++i)
		scanf("%d",&w[i]);
	for(i=1; i<=n; ++i) {
		scanf("%d%d",&c[i],&d[i]);
		a[c[i]]+=d[i];
		mx[c[i]]=max(mx[c[i]],a[c[i]]);
		mn[c[i]]=min(mn[c[i]],a[c[i]]);
	}
	bool flag=true;
	for(i=1; i<=m; ++i)
		flag=flag&&a[i]==0&&mx[i]-mn[i]<w[i];
	if(flag) {
		printf("-1");
		return 0;
	}
	if((n<=5&&m<=5)||(n<=100&&m<=3))
		return Subtask0::main();
	if(m==1)
		return Subtask1::main();
	return 0;
}