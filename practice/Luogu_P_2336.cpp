#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
using namespace std;
using vI = vector<int>;
const int N(5e4), M(1e5);
int n,m,q[M + 2];
vI p[N + 2];
namespace acam {
	const int S(1e5), logS(20);
	map<int,int> ch[S + 2];
	int tot,fail[S + 2],dep[S + 2],anc[S + 2][logS];
	namespace fenwick {
		int tr[S + 2];
		void add(int x,int f) {
			while(x<=tot) {
				tr[x]+=f;
				x+=x&(-x);
			}
		}
		void modify(int l,int r,int f) {
			add(l,f);
			add(r+1,-f);
		}
		int query(int x) {
			int r=0;
			while(x) {
				r+=tr[x];
				x&=x-1;
			}
			return r;
		}
		int sum(int l,int r) {
			return query(r)-query(l-1);
		}
	}
	int getFail(int u,int c) {
		if(ch[u].count(c)) return ch[u][c];
		if(!u) return 0;
		return ch[u][c]=getFail(fail[u],c);
	}
	vI insert(vI x) {
		int u=0;
		vI p{0};
		for(auto i : x) {
			if(!ch[u].count(i))
				ch[u][i]=++tot;
			p.push_back(u=ch[u][i]);
		}
		return p;
	}
	void build() {
		queue<int> q;
		for(auto [w,v] : ch[0])
			q.push(v);
		while(!q.empty()) {
			int u=q.front();
			q.pop();
			anc[u][0]=fail[u];
			dep[u]=dep[fail[u]]+1;
			for(int i=1; i<logS; ++i)
				anc[u][i]=anc[anc[u][i-1]][i-1];
			for(auto [w,v] : ch[u]) {
				fail[v]=getFail(fail[u],w);
				q.push(v);
			}
		}
	}
	int lca(int u,int v) {
		if(dep[u]<dep[v]) swap(u,v);
		for(int i=logS-1; i>=0; --i)
			if(dep[anc[u][i]]>=dep[v])
				u=anc[u][i];
		if(u==v) return u;
		for(int i=logS-1; i>=0; --i)
			if(anc[u][i]!=anc[v][i])
				u=anc[u][i],v=anc[v][i];
		return anc[u][0];
	}
}
vI read() {
	vI a;
	int k;
	scanf("%d",&k);
	a.resize(k);
	for(int &i : a)
		scanf("%d",&i);
	return a;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i) {
		vI a=read(),b=read();
		a.push_back(1e4+1);
		a.insert(a.end(),b.begin(),b.end());
		p[i]=acam::insert(a);
	}
	for(int i=1; i<=m; ++i) {
		q[i]=acam::insert(read()).back();
	}
	return 0;
}