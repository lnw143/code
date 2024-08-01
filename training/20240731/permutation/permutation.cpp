#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
using ll = long long;
using db = long double;
const int N = 40, P = 1e9 + 7;
const db eps = 1e-6;
int n,m,e[N + 2][N + 2][N + 2];
ll f[N + 2][N + 2][N + 2],fac[N + 2],inv[N + 2],ifac[N + 2],ans;
db s[N + 2][N + 2][N + 2];
struct point {
	int x,y;
} p[N + 2];
inline ll sqr(ll x) {
	return x*x;
}
inline bool eq(db a,db b) {
	return abs(a-b)<eps;
}
inline db operator-(const point& a,const point& b) {
	return sqrtl(sqr(a.x-b.x)+sqr(a.y-b.y));
}
inline db S(const point& A,const point& B,const point& C) {
	const db a=B-C,b=A-C,c=A-B,p=(a+b+c)/2;
	return sqrtl(p*(p-a)*(p-b)*(p-c));
}
inline bool check(int x,int a,int b,int c) {
	return eq(s[x][a][b]+s[x][b][c]+s[x][a][c],s[a][b][c]);
}
struct status {
	int i,j,k;
	db s;
} g[N * N * N];
inline ll ins(int n,int m) {
	return fac[n+m]*ifac[m]%P;
}
template<class T>
inline T& find(T f[N + 2][N + 2][N + 2],int x,int y,int z) {
	if(x>y) swap(x,y);
	if(y>z) swap(y,z);
	if(x>y) swap(x,y);
	return f[x][y][z];
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d%d",&p[i].x,&p[i].y);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			for(int k=1; k<=n; ++k)
				s[i][j][k]=S(p[i],p[j],p[k]);
	for(int i=1; i<=n; ++i)
		for(int j=i+1; j<=n; ++j)
			for(int k=j+1; k<=n; ++k) {
				for(int t=1; t<=n; ++t)
					if(t!=i&&t!=j&&t!=k&&check(t,i,j,k))
						++e[i][j][k];
				if(e[i][j][k]==n-3) f[i][j][k]=1;
				g[++m]={i,j,k,s[i][j][k]};
			}
	fac[0]=fac[1]=ifac[0]=ifac[1]=inv[1]=1;
	for(int i=2; i<=n; ++i) {
		fac[i]=fac[i-1]*i%P;
		inv[i]=(P-P/i)*inv[P%i]%P;
		ifac[i]=ifac[i-1]*inv[i]%P;
	}
	sort(g+1,g+m+1,[](auto x,auto y) { return x.s<y.s; });
	while(m) {
		auto [i,j,k,tmp]=g[m--];
		for(int t=1; t<=n; ++t)
			if(t!=i&&t!=j&&t!=k&&check(t,i,j,k)) {
				(find(f,t,i,j)+=f[i][j][k]*ins(find(e,t,j,k)+find(e,t,i,k),n-e[i][j][k]-3)%P)%=P;
				(find(f,t,j,k)+=f[i][j][k]*ins(find(e,t,j,i)+find(e,t,k,i),n-e[i][j][k]-3)%P)%=P;
				(find(f,t,i,k)+=f[i][j][k]*ins(find(e,t,i,j)+find(e,t,k,j),n-e[i][j][k]-3)%P)%=P;
			}
		(ans+=f[i][j][k]*ins(e[i][j][k],n-e[i][j][k]-3)%P)%=P;
	}
	printf("%lld",ans*fac[3]%P);
	return 0;
}