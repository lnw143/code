#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
const int N = 1e3, M = 10, L = 10, A = 4, P = 1e9 + 9;
map<char,int> mp{{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
int n,m;
char s[L + 2];
namespace acam {
	const int S = M * L;
	int tot,tr[S + 2][A + 2],fail[S + 2],dep[S + 2],len[S + 2];
	void insert(const char *s) {
		int u=0;
		for(int i=0; s[i]; ++i) {
			if(!tr[u][mp[s[i]]]) dep[tr[u][mp[s[i]]]=++tot]=dep[u]+1;
			u=tr[u][mp[s[i]]];
		}
		len[u]=dep[u];
	}
	void build() {
		static int que[S + 2];
		int h=0,t=0;
		for(int i=0; i<A; ++i)
			if(tr[0][i])	
				que[++t]=tr[0][i];
		while(h<t) {
			int u=que[++h];
			len[u]=max(len[u],len[fail[u]]);
			for(int i=0; i<A; ++i)
				if(tr[u][i])
					fail[tr[u][i]]=tr[fail[u]][i],que[++t]=tr[u][i];
				else
					tr[u][i]=tr[fail[u]][i];
		}
	}
}
int f[N + 2][L + 2][acam::S + 2];
int main() {
	using namespace acam;
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i) {
		scanf("%s",s);
		insert(s);
	}
	build();
	f[0][0][0]=1;
	for(int i=0; i<=n; ++i)
		for(int j=0; j<=L&&j<=i; ++j)
			for(int k=0; k<=tot; ++k)
				for(int p=0; p<A; ++p)
					if(len[tr[k][p]]>j)
						(f[i+1][0][tr[k][p]]+=f[i][j][k])%=P;
					else if(j<L)
						(f[i+1][j+1][tr[k][p]]+=f[i][j][k])%=P;
	int ans=0;
	for(int i=0; i<=tot; ++i)
		(ans+=f[n][0][i])%=P;
	printf("%d",ans);
	return 0;
}