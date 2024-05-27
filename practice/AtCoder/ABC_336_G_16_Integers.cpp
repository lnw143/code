#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
using ll = long long;
const int N(8), K(1e6), P(998244353);
int e[N][N],in[N],out[N],lap[N][N],fac[K + 2],ifac[K + 2],fa[N];
ll ans;
int find(int x) {
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
bool makeGraph() {
	memset(in,0,sizeof(in));
	memset(out,0,sizeof(out));
	memset(lap,0,sizeof(lap));
	memset(fa,0,sizeof(fa));
	for(int i=0; i<8; ++i) fa[i]=i,in[i]=out[i]=0;
	for(int i=0; i<8; ++i)
		for(int j=0; j<8; ++j) {
			lap[i][j]=-e[i][j];
			out[i]+=e[i][j];
			in[j]+=e[i][j];
			if(e[i][j]) fa[find(i)]=find(j);
		}
	int p=-1;
	for(int i=0; i<8; ++i)
		if(in[i]!=out[i]) return false;
		else if(in[i]) {
			if(p==-1) p=find(i);
			else if(find(i)!=p)
				return false;
		}
	for(int i=0; i<8; ++i) lap[i][i]+=in[i];
	return true;
}
ll det() {
	ll ans=1;
	for(int i=1; i<8; ++i) {
		for(int j=i+1; j<8; ++j) {
			while(lap[j][i]) {
				ll d=lap[i][i]/lap[j][i];
				for(int k=1; k<8; ++k)
					lap[i][k]=(lap[i][k]-d*lap[j][k]%P)%P;
				swap(lap[i],lap[j]);
				ans=-ans;
			}
		}
		if(lap[i][i]) ans=ans*lap[i][i]%P;
	}
	return ans;
}
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
int main() {
	fac[0]=1;
	for(ll i=1; i<=K; ++i) fac[i]=fac[i-1]*i%P;
	ifac[K]=qpow(fac[K],P-2);
	for(ll i=K-1; i>=1; --i) ifac[i]=ifac[i+1]*(i+1)%P;
	for(int i=0; i<16; ++i)
		scanf("%d",&e[i>>1][i&7]);
	for(int i=0; i<8; ++i)
		for(int j=0; j<8; ++j) {
			++e[i][j];
			if(makeGraph()) {
				ll ret=det();
				for(int k=0; k<8; ++k)
					if(in[k])
						ret=ret*fac[in[k]-1]%P;
				for(int u=0; u<8; ++u)
					for(int v=0; v<8; ++v)
						if(e[u][v]-(u==i&&v==j))
							ret=ret*ifac[e[u][v]-(u==i&&v==j)]%P;
				ans=(ans+ret)%P;
			}
			--e[i][j];
		}
	printf("%lld",(ans%P+P)%P);
	return 0;
}