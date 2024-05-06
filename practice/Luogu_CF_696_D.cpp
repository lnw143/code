#include<cstdio>
#include<algorithm>
using namespace std;
using ll = long long;
const int N = 200, S = 200, A = 26;
const ll inf = 1ll << 60;
int n,a[N + 2];
char s[S + 2];
ll l;
namespace acam {
	int tot,tr[S + 2][A + 2],fail[S + 2],f[S + 2];
	int insert(const char *s) {
		int u=0;
		for(int i=0; s[i]; ++i) {
			if(!tr[u][s[i]-'a']) tr[u][s[i]-'a']=++tot;
			u=tr[u][s[i]-'a'];
		}
		return u;
	}
	void build() {
		static int que[S + 2];
		int h=0,t=1;
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
struct matrix {
	int n,m;
	ll a[S + 2][S + 2];
	ll* operator[](int x) { return a[x]; }
	const ll* operator[](int x) const { return a[x]; }
	matrix(int n,int m):n(n),m(m) {}
};
matrix operator*(const matrix& x,const matrix& y) {
	matrix z(x.n,y.m);
	for(int i=0; i<=z.n; ++i)
		for(int j=0; j<=z.m; ++j) {
			z[i][j]=-inf;
			for(int k=0; k<=x.m; ++k)
				z[i][j]=max(z[i][j],x[i][k]+y[k][j]);
		}
	return z;
}
matrix qpow(matrix a,ll n) {
	matrix x(a.n,a.n);
	for(int i=0; i<=a.n; ++i) {
		for(int j=0; j<=a.n; ++j)
			x[i][j]=-inf;
		x[i][i]=0;
	}
	for(; n; n>>=1,a=a*a) if(n&1) x=x*a;
	return x;
}
int main() {
	scanf("%d%lld",&n,&l);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	using namespace acam;
	for(int i=1; i<=n; ++i) {
		scanf("%s",s);
		f[insert(s)]+=a[i];
	}
	build();
	matrix base(tot,tot);
	for(int i=0; i<=tot; ++i) {
		for(int j=0; j<=tot; ++j)
			base[i][j]=-inf;
		for(int j=0; j<A; ++j)
			base[i][tr[i][j]]=f[tr[i][j]];
		for(int j=0; j<=tot; ++j)
			printf("%lld ",max(-1ll,base[i][j]));
		putchar('\n');
	}
	matrix ori(0,tot);
	ori[0][0]=0;
	for(int i=1; i<=tot; ++i)
		ori[0][i]=-inf;
	// ori=ori*qpow(base,l);
	for(int i=1; i<=l; ++i) {
		ori=ori*base;
		for(int j=0; j<=tot; ++j)
			printf("%lld ",max(-1ll,ori[0][j]));
		putchar('\n');
	}
	ll ans=0;
	for(int i=0; i<=tot; ++i)
		ans=max(ans,ori[0][i]);
	printf("%lld",ans);
	return 0;
}