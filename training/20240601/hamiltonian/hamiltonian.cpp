#include <cstdio>
using namespace std;
using ll = long long;
const int N = 1e6;
int n,m,p[N + 2],a[N + 2],sz[N + 2],anc[N + 2];
int deg[N + 2],que[N + 2],ord[N + 2],cnt;
ll w[N + 2],d[N + 2];
char buf[20<<20],*l=buf;
bool bz[N + 2];

int read() {
	int x=0;
	bool f=0;
	while(*l<'0'||*l>'9') {
		if(*l=='-') f=1;
		l++;
	}
	for(; *l>='0'&&*l<='9'; l++) x=(x<<1)+(x<<3)+(*l^48);
	return f?n+1:x;
}

void topo() {
	for(int i=1; i<=n; ++i)
		++deg[p[i]];
	int h=0,t=0;
	for(int i=1; i<=n; ++i)
		if(deg[i]==0)
			que[++t]=i;
	++deg[n+1];
	while(h<t) {
		int u=que[++h];
		ord[++cnt]=u;
		if(--deg[p[u]]==0)
			que[++t]=p[u];
	}
	for(int i=1; i<=n; ++i)
		if(deg[i]>0) {
			int u=p[i];
			while(u!=i) {
				deg[u]=0;
				anc[u]=i;
				u=p[u];
			}
			ord[++cnt]=i;
			p[i]=n+1;
		}
}

bool check(ll x) {
	for(int i=1; i<=cnt; ++i) d[ord[i]]=sz[ord[i]]*x-w[ord[i]];
	d[n+1]=0;
	for(int i=1; i<=cnt; ++i)
		if(d[ord[i]]>0)
			d[p[ord[i]]]+=d[ord[i]];
	return d[n+1]<=m;
}

int solve() {
	ll l=0,r=2e9;
	while(l<=r) {
		int mid=(l+r)/2;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	return l-1;
}

int main() {
	freopen("hamiltonian.in","r",stdin);
	freopen("hamiltonian.out","w",stdout);
	fread(buf,1,20<<20,stdin);
	n=read(),m=read();
	for(int i=1; i<=n; ++i) p[i]=read();
	for(int i=1; i<=n; ++i) a[i]=read();
	for(int i=1; i<=n; ++i) anc[i]=i;
	topo();
	for(int i=1; i<=n; ++i)
		if(p[i]!=n+1)
			p[i]=anc[p[i]];
	for(int i=1; i<=n; ++i)
		w[anc[i]]+=a[i],++sz[anc[i]];
	printf("%d",solve());
	return 0;
}