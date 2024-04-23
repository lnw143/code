#include<cstdio>
#include<algorithm>
#include<bitset>
#include<map>
#define pw2(x) (1<<(x))
using namespace std;
const int N = 1e6 + 2;
using ll = long long;
int n,i,j,p[N],sz[N],em,e[N],ls[N],nx[N],hv[N];
ll f[N];
map<int,int> mp;
void insert(int x,int y) {
	e[++em]=y;
	nx[em]=ls[x];
	ls[x]=em;
}
template<int S=1> ll dp(int i) {
	if(S*2<=sz[i]) return dp<min(S<<1,N)>(i);
	bitset<S> g;
	g[0]=true;
	for(auto e : mp) {
		int siz=e.first,num=e.second;
		for(j=0; pw2(j)<=num; ++j) {
			g|=g<<(siz<<j);
			num-=pw2(j);
		}
		if(num)	g|=g<<(siz*num);
	}
	ll maxn=0;
	for(j=1; j*2<=sz[i]; ++j)
		if(g[j])
			maxn=max(maxn,(ll)j*(sz[i]-1-j));
	return maxn;
}
int main() {
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
	scanf("%d",&n);
	for(i=2; i<=n; ++i) {
		scanf("%d",&p[i]);
		insert(p[i],i);
	}
	for(i=n; i>=1; --i) {
		sz[p[i]]+=sz[i]+=1;
		for(j=ls[i]; j; j=nx[j])
			if(!hv[i]||sz[e[j]]>sz[hv[i]]) hv[i]=e[j];
		if(sz[hv[i]]*2>=sz[i]-1) f[p[i]]+=f[i]+=(ll)sz[hv[i]]*(sz[i]-1-sz[hv[i]]);
		else {
			mp.clear();
			for(j=ls[i]; j; j=nx[j])
				++mp[sz[e[j]]];
			f[p[i]]+=f[i]+=dp(i);
		}
	}
	printf("%lld",f[1]);
	return 0;
}