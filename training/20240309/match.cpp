#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N(1e2), M(10), K(8), T(30), S(1 << K), P(1e9 + 7);
int n,m,k,t[K + 2][T + 2],len[K + 2];
char s[K + 2][T + 2],sigma[M + 2];
int Map(char c) {
	char *p=lower_bound(sigma,sigma+m,c);
	return c==*p?p-sigma:-1;
}
namespace acam {
	const int S_(K * T + 2);
	int tot,ch[S_][M + 2],fail[S_],g[S_];
	int& insert(int s[],int n) {
		int u=0;
		for(int i=0; i<n; ++i) {
			if(!ch[u][s[i]]) ch[u][s[i]]=++tot;
			u=ch[u][s[i]];
		}
		return g[u];
	}
	void build() {
		static int que[S_],h,t;
		h=t=0;
		for(int i=0; i<m; ++i)
			if(ch[0][i])
				que[++t]=ch[0][i];
		while(h<t) {
			int u=que[++h];
			g[u]|=g[fail[u]];
			for(int i=0; i<m; ++i)
				if(ch[u][i])
					fail[ch[u][i]]=ch[fail[u]][i],que[++t]=ch[u][i];
				else
					ch[u][i]=ch[fail[u]][i];
		}
	}
}
int dp() {
	using namespace acam;
	static int f[N + 2][S_][S + 2];
	f[0][0][0]=1;
	int sta=1<<k;
	for(int i=0; i<n; ++i)
		for(int u=0; u<=tot; ++u)
			for(int j=0; j<sta; ++j)
				if(f[i][u][j])
					for(int v=0; v<m; ++v)
						(f[i+1][ch[u][v]][j|g[ch[u][v]]]+=f[i][u][j])%=P;
	int ans=0;
	for(int u=0; u<=tot; ++u)
		ans=(ans+f[n][u][sta-1])%P;
	return ans;
}
int main() {
	scanf("%d%d",&n,&k);
	for(int i=1; i<=k; ++i)
		scanf("%s",s[i]),len[i]=strlen(s[i]);
	scanf("%d%s",&m,sigma);
	sort(sigma,sigma+m);
	m=unique(sigma,sigma+m)-sigma;
	for(int i=1; i<=k; ++i) {
		for(int j=0; j<len[i]; ++j)
			if((t[i][j]=Map(s[i][j]))==-1)
				return printf("0"),0;
		acam::insert(t[i],len[i])|=1<<(i-1);
	}
	acam::build();
	printf("%d",dp());
	return 0;
}