#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define Noans() printf("0"),0
using namespace std;
using ll = long long;
const int N(16), M(N >> 1), K(1e6), P(998244353);
int n=N,m=n>>1,x[N + 2],du[M + 2],di[M + 2],odd[M + 2],cnt,lap[M + 2][M + 2],fac[K + 2];
namespace dsu {
	int fa[M + 2];
	int find(int x) {
		return fa[x]==x?x:fa[x]=find(fa[x]);
	}
	struct TMP { TMP() {
		for(int i=0; i<m; ++i)
			fa[i]=i;
	} } tmp;
}
void link(int x,int y,int z) {
	lap[x][y]-=z;
	du[x]+=z;
	di[y]+=z;
}
ll det() {
	static ll a[M + 2][M + 2];
	for(int i=0; i<m; ++i)
		for(int j=0; j<m; ++j)
			a[i][j]=(lap[i][j]+P)%P;//,printf("%d%c",a[i][j]," \n"[j==m-1]);
	ll ans=1;
	for(int i=0; i<m-1; ++i) {
		for(int j=i+1; j<m-1; ++j)
			while(a[j][i]) {
				ll d=a[i][i]/a[j][i];
				for(int k=i; k<m-1; ++k)
					a[i][k]=(a[i][k]-d*a[j][k]%P)%P;
				swap(a[i],a[j]);
				ans=-ans;
			}
		if(a[i][i]) ans=ans*a[i][i]%P;
	}
	return (ans+P)%P;
}
int calc(int s,int t) {
	link(t,s,1);
	for(int i=0; i<m; ++i)
		lap[i][i]=di[i];
	ll ans=det();
	for(int i=0; i<m; ++i)
		if(du[i])
			ans=ans*fac[du[i]-1]%P;
	link(t,s,-1);
	return ans;
}
int main() {
	fac[0]=1;
	for(ll i=1; i<=K; ++i)
		fac[i]=i*fac[i-1]%P;
	using namespace dsu;
	for(int i=0; i<n; ++i) {
		scanf("%d",&x[i]);
		link(i>>1,i&7,x[i]);
		if(x[i]) fa[find(i>>1)]=find(i&7);
	}
	set<int> st;
	for(int i=0; i<m; ++i)
		if(di[i])
			st.insert(find(i));
	if(st.size()!=1) return Noans();
	int s=-1,t=-1;
	for(int i=0; i<m; ++i) {
		if(abs(du[i]-di[i])>1) return Noans();
		if(du[i]<di[i]) {
			if(~t) return Noans();
			t=i;
		}
		if(du[i]>di[i]) {
			if(~s) return Noans();
			s=i;
		}
	}
	int ans=0;
	if(~s) {
		if(t==-1) return Noans();
		ans=calc(s,t);
	} else {
		if(~t) return Noans();
		for(int i=0; i<m; ++i)
			ans=(ans+calc(i,i))%P;
	}
	printf("%d",ans);
	return 0;
}