#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
using ll = long long;
using vi = vector<int>;
const int N(5e5), A(26);
const ll inf(1ll<<60);
int n,i,j,v[N + 2],p[N + 2];
ll ans;
vi s[N + 2];
char chr[N + 2];
namespace ACAM {
	int tot,tr[N + 2][A + 2],fail[N + 2];
	vi e[N + 2];
	namespace DFS {
		int dfc,dfn[N + 2],low[N + 2];
		void dfs(int u) {
			dfn[u]=++dfc;
			for(int v : e[u])
				dfs(v);
			low[u]=dfc;
		}
	}
	using namespace DFS;
	int insert(vi s) {
		int u=0;
		for(int c : s) {
			if(!tr[u][c]) tr[u][c]=++tot;
			u=tr[u][c];
		}
		return u;
	}
	void build() {
		queue<int> q;
		for(int i=0; i<A; ++i)
			if(tr[0][i])
				q.push(tr[0][i]);
		while(!q.empty()) {
			int u=q.front();
			q.pop();
			e[fail[u]].push_back(u);
			for(int i=0; i<A; ++i)
				if(!tr[u][i])
					tr[u][i]=tr[fail[u]][i];
				else
					fail[tr[u][i]]=tr[fail[u]][i],q.push(tr[u][i]);
		}
		dfs(0);
	}
}
using namespace ACAM;
namespace Segtree {
	const int S((N << 2) + 2);
	ll tr[S],lzy[S];
#define ls (x<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
#define upd(x,y) x=max(x,y)
	void dwtg(int x,int l,int r) {
		if(l<r) {
			upd(lzy[ls],lzy[x]);
			upd(lzy[rs],lzy[x]);
			upd(tr[ls],lzy[ls]);
			upd(tr[rs],lzy[rs]);
		}
	}
	void modify(int x,int l,int r,int L,int R,ll f) {
		if(r<L||R<l) return ;
		dwtg(x,l,r);
		if(L<=l&&r<=R) {
			upd(lzy[x],f);
			dwtg(x,l,r);
			return ;
		}
		int mid=(l+r)/2;
		modify(li,L,R,f);
		modify(ri,L,R,f);
		tr[x]=max(tr[ls],tr[rs]);
		return ;
	}
	ll query(int x,int l,int r,int g) {
		if(r<g||g<l) return -inf;
		if(l==r) return tr[x];
		dwtg(x,l,r);
		int mid=(l+r)/2;
		return g<=mid?query(li,g):query(ri,g);
	}
}
ll findmax(vi s) {
	int u=0;
	ll r=0;
	for(int c : s) {
		u=tr[u][c];
		upd(r,Segtree::query(1,1,dfc,dfn[u]));
	}
	return r;
}
int main() {
	freopen("word.in","r",stdin);
	freopen("word.out","w",stdout);
	scanf("%d",&n);
	for(i=1; i<=n; ++i) {
		scanf("%s%d",chr,&v[i]);
		for(j=0; chr[j]; ++j)
			s[i].push_back(chr[j]-'a');
		p[i]=insert(s[i]);
	}
	build();
	for(i=1; i<=n; ++i) {
		ll val=findmax(s[i])+v[i];
		ans=max(ans,val);
		Segtree::modify(1,1,dfc,dfn[p[i]],low[p[i]],val);
	}
	printf("%lld",ans);
	return 0;
}