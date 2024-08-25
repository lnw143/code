#include <cstdio>
#include <algorithm>
using namespace std;
using ll = __int128_t;
const int N = 16;
int T,n,a,b,c,q,p[N + 2];
int s[N + 2],tau[N + 2][N * N];
struct frac {
	ll p,q;
};
frac operator*(const frac& a,const frac& b) {
	return {a.p*b.p, a.q*b.q};
}
frac operator/(const frac& a,const frac& b) {
	return {a.p*b.q, a.q*b.p};
}
struct solution {

}
int main() {
	freopen("perm.in","r",stdin);
	freopen("perm.out","w",stdout);
	tau[1][0]=1;
	for(int i=1; i<N; ++i) {
		s[i]=i*(i-1)/2;
		for(int j=0; j<=s[i]; ++i)
			for(int k=0; k<=i; ++k)
				tau[i+1][j+k]+=tau[i][j];
	}
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d%d%d%d",&n,&a,&b,&c,&q);
		
	}
	return 0;
}