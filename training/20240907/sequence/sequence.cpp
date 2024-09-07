#include <cstdio>
#include <algorithm>
inline char gc() {
	static char buf[1<<16],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,1<<16,stdin),l==r)?-1:*l++;
}
inline int read() {
	int x=0;
	char c=gc();
	for(; c<'0'||c>'9'; c=gc());
	for(; c>='0'&&c<='9'; c=gc()) x=(x<<1)+(x<<3)+(c&15);
	return x;
}
using namespace std;
using ll = long long;
const int N = 1e5;
int n,k,a[N + 2];
namespace ST {
	const int logN = 18;
	int s[logN][N + 2],t[logN][N + 2];
	void init() {
		for(int j=1; j<logN; ++j)
			for(int i=1; i<=n-(1<<j)+1; ++i)
				s[j][i]=s[j-1][i]|s[j-1][i+(1<<(j-1))],
				t[j][i]=t[j-1][i]&t[j-1][i+(1<<(j-1))];
	}
	int query(int l,int r) {
		int k=__lg(r-l+1);
		return (s[k][l]|s[k][r-(1<<k)+1])^(t[k][l]&t[k][r-(1<<k)+1]);
	}
}
namespace dp {
	ll f[N + 2];
	int g[N + 2],lt[N + 2],rt[N + 2],q[N + 2];
	inline ll cost(int j,int i) {
		return f[j]+ST::query(j+1,i);
	}
	void solve(ll C) {
		f[0]=0;
		g[0]=0;
		int h=1,t=1;
		q[1]=0;
		lt[0]=1;
		rt[0]=n;
		for(int i=1; i<=n; ++i) {
			while(h<=t&&rt[q[h]]<i) ++h;
			f[i]=cost(q[h],i)-C;
			g[i]=g[q[h]]+1;
			while(h<=t&&cost(q[t],max(i+1,lt[q[t]]))<cost(i,max(i+1,lt[q[t]]))) --t;
			if(i==n) break;
			if(h>t) {
				lt[i]=i+1;
				rt[i]=n;
				q[++t]=i;
			} else if(cost(q[t],rt[q[t]])<cost(i,rt[q[t]])) {
				int l=max(i+1,lt[q[t]]),r=rt[q[t]];
				while(l<=r) {
					int mid=(l+r)/2;
					if(cost(q[t],mid)<cost(i,mid)) r=mid-1;
					else l=mid+1;
				}
				rt[q[t]]=l-1;
				lt[i]=l;
				rt[i]=n;
				q[++t]=i;
			} else if(rt[q[t]]<n) {
				lt[i]=rt[q[t]]+1;
				rt[i]=n;
				q[++t]=i;
			}
		}
	}
}
int main() {
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	n=read();
	k=read();
	for(int i=1; i<=n; ++i) ST::s[0][i]=ST::t[0][i]=read();
	ST::init();
	ll l=-(1<<30),r=1<<30;
	while(l<=r) {
		ll mid=(l+r)/2;
		dp::solve(mid);
		if(dp::g[n]<=k) r=mid-1;
		else l=mid+1;
	}
	dp::solve(r+1);
	printf("%lld",dp::f[n]+k*(r+1));
	return 0;
}