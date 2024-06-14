#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <deque>
#include <cstring>
#include <algorithm>

using namespace std;

using veci = vector<int>;
using ll = long long;

// persistent segtree
namespace segtree {
	const int N = 4e5 + 5;
	const int S = N << 6;
#define mid ((l+r)>>1)
	int tot,s[S + 2],ls[S + 2],rs[S + 2];
	int build(int l,int r) {
		int u=++tot;
		if(l==r) return u;
		ls[u]=build(l,mid);
		rs[u]=build(mid+1,r);
		return u;
	}
	int modify(int u,int l,int r,int x) {
		int v=++tot;
		ls[v]=ls[u],rs[v]=rs[u];
		if(l==r) {
			s[v]=s[u]+1;
			return v;
		}
		if(x<=mid) ls[v]=modify(ls[v],l,mid,x);
		else rs[v]=modify(rs[v],mid+1,r,x);
		s[v]=s[ls[v]]+s[rs[v]];
		return v;
	}
	int query(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return 0;
		if(x<=l&&r<=y) return s[u];
		return query(ls[u],l,mid,x,y)+query(rs[u],mid+1,r,x,y);
	}
#undef mid
}

namespace solution {
	const int N = 1e5, M = 1e5, D = 4e5;
	const ll inf = 1ll << 60;
	int n,m,d,t[N + 2],lt[M + 2],rt[M + 2];
	int root[D + 2];
	ll f[M + 2];
	struct edge {
		int x,y,a,b,c;
	} e[M + 2];
	deque<int> q[N + 2];
	struct HeapCmp { bool operator()(int x,int y) { return e[x].b>e[y].b; } };
	priority_queue<int,vector<int>,HeapCmp> hp[N + 2];
	ll count(int l,int r) { 
		return segtree::query(root[r],0,d,l,r);
	}
	ll cost(int u,int v) {
		if(v<e[u].b) return inf;
		return f[u]+count(e[u].b,v)*t[e[u].y];
	}
	void putQ(int u) {
		if(f[u]==inf) return ;
		auto& Q=q[e[u].y];
		while(!Q.empty()&&cost(Q.back(),lt[Q.back()])>cost(u,lt[Q.back()])) Q.pop_back();
		if(Q.empty()) {
			lt[u]=e[u].b;
			rt[u]=d;
			Q.push_back(u);
		} else if(cost(Q.back(),rt[Q.back()])>cost(u,rt[Q.back()])) {
			int l=lt[Q.back()],r=rt[Q.back()];
			while(l<=r) {
				int mid=(l+r)/2;
				if(cost(Q.back(),mid)>cost(u,mid)) r=mid-1;
				else l=mid+1;
			}
			rt[Q.back()]=r;
			lt[u]=r+1;
			rt[u]=d;
			Q.push_back(u);
		} else if(rt[Q.back()]<d) {
			lt[u]=rt[Q.back()]+1;
			rt[u]=d;
			Q.push_back(u);
		}
	}
	ll solve() {
		f[0]=0;
		e[0].b=0;
		e[0].y=1;
		lt[0]=0,rt[0]=d;
		putQ(0);
		++m;
		e[m].x=e[m].y=n;
		e[m].a=d,e[m].b=d+1;
		for(int i=1; i<=m; ++i) {
			auto &heap = hp[e[i].x];
			while(!heap.empty()&&e[heap.top()].b<=e[i].a) {
				putQ(heap.top());
				heap.pop();
			}
			auto& Q=q[e[i].x];
			while(!Q.empty()&&rt[Q.front()]<e[i].a) Q.pop_front();
			if(Q.empty()) f[i]=inf;
			else f[i]=cost(Q.front(),e[i].a)+e[i].c;
			hp[e[i].y].push(i);
		}
		return f[m]==inf?-1:f[m];
	}
}

ll solve(int n_, int m_, int w_, veci T, veci X, veci Y, veci A, veci B, veci C, veci L, veci R) {
	using solution::d;
	{ // discrete
		veci v;
		for(auto a : {&A, &B, &L, &R}) for(auto &i : *a) v.push_back(i);
		sort(v.begin(),v.end());
		v.erase(unique(v.begin(),v.end()),v.end());	
		d=v.size()+1;
		for(auto a : {&A, &B, &L, &R}) for(auto &i : *a) i=lower_bound(v.begin(),v.end(),i)-v.begin()+1;
	}
	{ // build segtree
		using namespace segtree;
		vector<veci> e(d+1);
		for(int i=0; i<w_; ++i) e[R[i]+1].push_back(L[i]-1);
		using solution::root;
		root[0]=build(0,d);
		for(int i=1; i<=d; ++i) {
			root[i]=root[i-1];
			for(auto j : e[i]) root[i]=modify(root[i],0,d,j);
		}
	}
	{ // sort edges
		veci p(m_);
		for(int i=0; i<m_; ++i) p[i]=i;
		sort(p.begin(),p.end(),[&](int x,int y) {
			return A[x]<A[y];
		});
		for(int i=1; i<=m_; ++i) solution::e[i]={X[p[i-1]]+1,Y[p[i-1]]+1,A[p[i-1]],B[p[i-1]],C[p[i-1]]};
	}
	{ // init
		using namespace solution;
		n=n_,m=m_;
		for(int i=0; i<n; ++i) t[i+1]=T[i];
	}
	return solution::solve();
}