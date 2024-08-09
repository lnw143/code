#include <cstdio>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 8e4, logN = 18;
int n,q,t[N + 2];
vector<int> e[N + 2],num;
namespace tree {
	int anc[logN][N + 2],dep[N + 2],low[N + 2],dfn[N + 2],dfc;
	void dfs(int u,int p) {
		anc[0][u]=p;
		dep[u]=dep[p]+1;
		for(int i=1; i<logN; ++i)
			anc[i][u]=anc[i-1][anc[i-1][u]];
		dfn[u]=++dfc;
		for(auto v : e[u])
			if(v!=p)
				dfs(v,u);
		low[u]=dfc;
	}
	int lca(int u,int v) {
		if(dep[u]>dep[v]) swap(u,v);
		for(int i=logN-1; ~i; --i)
			if(dep[anc[i][v]]>=dep[u])
				v=anc[i][v];
		if(u==v) return u;
		for(int i=logN-1; ~i; --i)
			if(anc[i][u]!=anc[i][v])
				u=anc[i][u],
				v=anc[i][v];
		return anc[0][u];
	}
}
namespace fenwick {
	int s[N + 2];
	void add(int x,int v) {
		for(int i=x; i<=n; i+=i&-i) s[i]+=v;
	}
	void add(int l,int r,int v) {
		add(l,v);
		add(r+1,-v);
	}
	int sum(int x) {
		int res=0;
		for(int i=x; i; i&=i-1) res+=s[i];
		return res;
	}
}
int cnt,ans[N * 3 + 2];
struct operation {
	int a,b,k;
	operation(int a,int b,int k=0):a(a),b(b),k(k) {}
	operation()=default;
} qr[N + 2],op[N * 3 + 2];
void solve(int l,int r,vector<int> Q) {
	if(Q.empty()) return ;
	if(l==r) {
		for(auto i : Q)
			ans[i]=l;
		return ;
	}
	int mid=(l+r)/2;
	vector<int> Ql,Qr;
	for(auto i : Q) {
		auto &[a,b,k]=op[i];
		if(k==0) {
			if(abs(b)<=mid) fenwick::add(tree::dfn[a],tree::low[a],b<0?-1:1),Ql.push_back(i);
			else Qr.push_back(i);
		} else {
			int l=tree::lca(a,b),f=tree::anc[0][l];
			int res=fenwick::sum(tree::dfn[a])+fenwick::sum(tree::dfn[b])-fenwick::sum(tree::dfn[l]);
			if(l!=1) res-=fenwick::sum(tree::dfn[f]);
			if(k<=res) Ql.push_back(i);
			else {
				k-=res;
				Qr.push_back(i);
			}
		}
	}
	for(auto i : Ql) {
		auto [a,b,k]=op[i];
		if(k==0) fenwick::add(tree::dfn[a],tree::low[a],b<0?1:-1);
	}
	solve(l,mid,Ql);
	solve(mid+1,r,Qr);
}
int main() {
	scanf("%d%d",&n,&q);
	for(int i=1; i<=n; ++i) scanf("%d",&t[i]);
	for(int i=1; i<n; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1; i<=q; ++i) scanf("%d%d%d",&qr[i].k,&qr[i].a,&qr[i].b);
	for(int i=1; i<=n; ++i) num.push_back(t[i]);
	for(int i=1; i<=q; ++i)
		if(qr[i].k==0)
			num.push_back(qr[i].b);
	sort(num.begin(),num.end(),greater<int>());
	num.erase(unique(num.begin(),num.end()),num.end());
	for(int i=1; i<=n; ++i) t[i]=lower_bound(num.begin(),num.end(),t[i],greater<int>())-num.begin()+1;
	for(int i=1; i<=q; ++i)
		if(qr[i].k==0)
			qr[i].b=lower_bound(num.begin(),num.end(),qr[i].b,greater<int>())-num.begin()+1;
	for(int i=1; i<=n; ++i)
		op[++cnt]=operation(i,t[i]);
	for(int i=1; i<=q; ++i)
		if(qr[i].k==0) {
			auto [a,b,k]=qr[i];
			op[++cnt]=operation(a,-t[a]);
			op[++cnt]=operation(a,b);
			t[a]=b;
		} else 
			op[++cnt]=qr[i];
	tree::dfs(1,1);
	vector<int> Q;
	for(int i=1; i<=cnt; ++i) Q.push_back(i);
	solve(1,num.size()+1,Q);
	for(int i=1; i<=cnt; ++i)
		if(op[i].k) {
			if(ans[i]>num.size()) printf("invalid request!\n");
			else printf("%d\n",num[ans[i]-1]);
		}
	return 0;
}