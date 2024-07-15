#include <cstdio>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 1e5, logA = 30, logN = 20;
int T;
int n,q,a[N + 2];
int l[N + 2],r[N + 2],ans[N + 2];
int rt[N + 2];
int anc[logN][N + 2],lim[logN][N + 2];
namespace trie01 {
	const int S = N << 5;
	int tot,ch[S][2],s[S],t[S];
	int modify(int u,int p,int x) {
		int v=++tot,rt=v;
		for(int i=logA-1; i>=0; --i) {
			ch[v][0]=ch[u][0];
			ch[v][1]=ch[u][1];
			s[v]=s[u]+1;
			t[v]=p;
			ch[v][(x>>i)&1]=++tot;
			u=ch[u][(x>>i)&1];
			v=ch[v][(x>>i)&1];
		}
		s[v]=s[u]+1;
		t[v]=p;
		return rt;
	}
	pair<int,int> find_max(int u,int v,int x) {
		int res=0;
		for(int i=logA-1; i>=0; --i)
			if(s[ch[v][!((x>>i)&1)]]>s[ch[u][!((x>>i)&1)]])
				u=ch[u][!((x>>i)&1)],
				v=ch[v][!((x>>i)&1)],
				res|=1<<i;
			else
				u=ch[u][(x>>i)&1],
				v=ch[v][(x>>i)&1];
		return {res,t[v]};
	}
	int find_greater(int u,int v,int x,int y) {
		int p=0;
		for(int i=logA-1; i>=0; --i) {
			if(!((y>>i)&1)&&s[ch[v][!((x>>i)&1)]]>s[ch[u][!((x>>i)&1)]])
				p=max(p,t[ch[v][!((x>>i)&1)]]);
			u=ch[u][((x^y)>>i)&1];
			v=ch[v][((x^y)>>i)&1];
		}
		return p;
	}
}
void solve(int L,int R,const vector<int>& q) {
	if(L==R) return ;
	const int mid=(L+R)/2;
	for(int j=0; j<logN; ++j) anc[j][mid+1]=1,lim[j][mid+1]=0;
	for(int i=mid+2; i<=R; ++i) {
		auto [maxn,maxp]=trie01::find_max(rt[mid],rt[i-1],a[i]);
		lim[0][i]=trie01::find_greater(rt[0],rt[mid],a[i],maxn);
		anc[0][i]=maxp;
		for(int j=1; j<logN; ++j)
			anc[j][i]=anc[j-1][anc[j-1][i]],
			lim[j][i]=max(lim[j-1][i],lim[j-1][anc[j-1][i]]);
	}
	vector<int> s,t;
	for(auto i : q)
		if(r[i]<=mid)
			s.push_back(i);
		else if(mid<l[i])
			t.push_back(i);
		else {
			s.push_back(i);
			int &u=r[i];
			for(int j=logN-1; j>=0; --j)
				if(anc[j][u]>mid&&lim[j][u]<l[i])
					u=anc[j][u],ans[i]+=1<<j;
			u=trie01::find_max(rt[l[i]-1],rt[u-1],a[u]).second;
			++ans[i];
		}
	solve(L,mid,s);
	solve(mid+1,R,t);
}
int main() {
	freopen("hogrider.in","r",stdin);
	freopen("hogrider.out","w",stdout);
	scanf("%d",&T);
	while(T--) {
		trie01::tot=0;
		scanf("%d%d",&n,&q);
		for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
		for(int i=1; i<=q; ++i)
			scanf("%d%d",&l[i],&r[i]),ans[i]=0;
		for(int i=1; i<=n; ++i)
			rt[i]=trie01::modify(rt[i-1],i,a[i]);
		vector<int> queries;
		for(int i=1; i<=q; ++i) queries.push_back(i);
		solve(1,n,queries);
		for(int i=1; i<=q; ++i)
			printf("%d\n",ans[i]);
	}
	return 0;
}