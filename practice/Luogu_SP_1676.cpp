#include<cstdio>
#include<cstring>
using namespace std;
const int N = 10, S = N * 6, L = 1e6, A = 26, P = 10007;
int n,l,f[L + 2][S + 2][2];
char s[8];
namespace acam {
	int tot,tr[S + 2][A + 2],fail[S + 2];
	bool g[S + 2];
	void insert(const char *s) {
		int u=0;
		for(int i=0; s[i]; ++i) {
			if(!tr[u][s[i]-'A']) tr[u][s[i]-'A']=++tot;
			u=tr[u][s[i]-'A'];
		}
		g[u]=true;
	}
	void build() {
		static int que[S + 2];
		int h=0,t=0;
		for(int i=0; i<A; ++i)
			if(tr[0][i])
				que[++t]=tr[0][i];
		while(h<t) {
			int u=que[++h];
			g[u]=g[u]||g[fail[u]];
			for(int i=0; i<A; ++i)
				if(tr[u][i])
					fail[tr[u][i]]=tr[fail[u]][i],que[++t]=tr[u][i];
				else
					tr[u][i]=tr[fail[u]][i];
		}
	}
	void clean() {
		for(int i=0; i<=tot; ++i) {
			memset(tr[i],0,sizeof(tr[i]));
			fail[i]=g[i]=0;
		}
		tot=0;
	}
}
struct matrix {
	int n,m,a[S + 2][S + 2];
	int* operator[](int x) { return a[x]; }
	const int* operator[](int x) const { return a[x]; }
	matrix(int n,int m) : n(n),m(m) {
		for(int i=0; i<=n; ++i)
			for(int j=0; j<=m; ++j)
				a[i][j]=0;
	}
};
matrix operator*(const matrix& x,const matrix& y) {
	matrix z(x.n,y.m);
	for(int i=0; i<=z.n; ++i)
		for(int j=0; j<=z.m; ++j)
			for(int k=0; k<=x.m; ++k)
				(z[i][j]+=x[i][k]*y[k][j]%P)%=P;
	return z;
}
matrix qpow(matrix a,int n) {
	matrix x(a.n,a.n);
	for(int i=0; i<=a.n; ++i) x[i][i]=1;
	for(; n; n>>=1,a=a*a) if(n&1) x=x*a;
	return x;
}
int qpow(int a,int n) {
	int x=1;
	for(; n; n>>=1,a=(long long)a*a%P) if(n&1) x=(long long)x*a%P;
	return x;
}
int main() {
	while(scanf("%d%d",&n,&l)==2) {
		using namespace acam;
		for(int i=1; i<=n; ++i) {
			scanf("%s",s);
			insert(s);
		}
		build();
		matrix base(tot,tot),ans(0,tot);
		for(int i=0; i<=tot; ++i)
			for(int j=0; j<A; ++j)
				if(!g[i]&&!g[tr[i][j]])
					++base[i][tr[i][j]];
		ans[0][0]=1;
		ans=ans*qpow(base,l);
		int ans2=0;
		for(int i=0; i<=tot; ++i)
			if(!g[i]) ans2=(ans2+ans[0][i])%P;
		ans2=qpow(26,l)-ans2;
		printf("%d\n",(ans2%P+P)%P);
		clean();
	}
	return 0;
}