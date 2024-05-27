#include<cstdio>
#include<cstring>
using namespace std;
const int N = 1e3, M = 1e2, A = 1 << 7;
int T,n,m,h,w,c[M + 2],d[N + 2][N + 2],kmp[N + M + 5];
char a[N + 2][N + 2],b[M + 2][M + 2];
namespace acam {
	const int S = M * M;
	int tot,tr[S + 2][A + 2],fail[S + 2];
	int insert(const char *s) {
		int u=0;
		for(int i=0; s[i]; ++i) {
			if(!tr[u][s[i]]) tr[u][s[i]]=++tot;
			u=tr[u][s[i]];
		}
		return u;
	}
	void clean() {
		tot=0;
		memset(tr,0,sizeof(tr));
		memset(fail,0,sizeof(fail));
	}
	void build() {
		static int que[S + 2];
		int h=0,t=0;
		for(int i=0; i<A; ++i)
			if(tr[0][i])	
				que[++t]=tr[0][i];
		while(h<t) {
			int u=que[++h];
			for(int i=0; i<A; ++i)
				if(tr[u][i])
					fail[tr[u][i]]=tr[fail[u]][i],que[++t]=tr[u][i];
				else
					tr[u][i]=tr[fail[u]][i];
		}

	}
}
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		for(int i=1; i<=n; ++i)
			scanf("%s",a[i]+1);
		scanf("%d%d",&h,&w);
		for(int i=1; i<=h; ++i)
			scanf("%s",b[i]+1);
		using namespace acam;
		for(int i=1; i<=h; ++i)
			c[i]=insert(b[i]+1);
		build();
		for(int i=1; i<=n; ++i) {
			int u=0;
			for(int j=1; j<=m; ++j)
				d[i][j]=u=tr[u][a[i][j]];
		}
		for(int i=2; i<=h; ++i) {
			int j=kmp[i-1];
			while(j&&c[j+1]!=c[i]) j=kmp[j];
			if(c[j+1]==c[i]) ++j;
			kmp[i]=j;
		}
		kmp[h+1]=0;
		int ans=0;
		for(int j=w; j<=m; ++j)
			for(int i=1; i<=n; ++i) {
				int k=kmp[h+i];
				while(k&&(k==h||c[k+1]!=d[i][j])) k=kmp[k];
				if(k<h&&c[k+1]==d[i][j]) ++k;
				kmp[h+i+1]=k;
				if(k==h) ++ans;
			}
		printf("%d\n",ans);
		clean();
	}
	return 0;
}