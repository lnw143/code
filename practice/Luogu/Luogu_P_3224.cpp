#include <cstdio>
#include <random>
#include <chrono>
using namespace std;
const int N = 1e5;
int n,m,q,p[N + 2],v[N + 2];
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct treap {
	struct node {
		int ls,rs,val,siz;
		unsigned int pri;
	};
	vector<node> s;
	int rt;
	int merge(int u,int v) {
		if(!u||!v) return u|v;
		if(s[u].pri<s[v].pri) return s[u].rs=merge(s[u].rs,v),pushup(u),u;
		else return s[v].ls=merge(u,s[v].ls),pushup(v),v;
	}
	void spRnk(int u,int v,int &x,int &y) {
		if(!u) return x=y=0,void();
		if(s[s[u].ls].siz+1<=v) x=u,spRnk(s[u].rs,v-s[s[u].ls].siz-1,s[u].rs,y);
		else y=u,spRnk(s[u].ls,v,x,s[u].ls);
		pushup(u);
	}
	void spVal(int u,int v,int &x,int &y) {
		if(!u) return x=y=0,void();
		if(s[u].val<=v) x=u,spVal(s[u].rs,v,s[u].rs,y);
		else y=u,spVal(s[u].ls,v,x,s[u].ls);
		pushup(u);
	}
	void pushup(int u) {
		s[u].siz=s[s[u].ls].siz+s[s[u].rs].siz+1;
	}
	int newnode(int v) {
		s.push_back({0,0,v,1,rnd()});
		return s.size()-1;
	}
	void insert(int v) {
		int x=0,y=0;
		spVal(rt,v,x,y);
		rt=merge(merge(x,newnode(v)),y);
	}
	int operator[](int k) {
		if(k>size()) return -1;
		int x=0,y=0,z=0;
		spRnk(rt,k,x,y);
		spRnk(x,k-1,x,z);
		int res=s[z].val;
		rt=merge(merge(x,z),y);
		return res;
	}
	int size() {
		return s.size()-1;
	}
	void clean() {
		rt=0;
		s.clear();
		s.resize(1);
	}
	treap() {
		clean();
	}
} tr[N + 2];
namespace dsu {
	int fa[N + 2];
	void init() {
		for(int i=1; i<=n; ++i) fa[i]=i;
	}
	int find(int u) {
		return fa[u]==u?u:fa[u]=find(fa[u]);
	}
}
void merge(int u,int v) {
	u=dsu::find(u),v=dsu::find(v);
	if(u==v) return ;
	if(tr[u].size()>tr[v].size()) swap(u,v);
	for(int i=1; i<tr[u].s.size(); ++i)
		tr[v].insert(tr[u].s[i].val);
	tr[u].clean();
	dsu::fa[u]=v;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%d",&p[i]),v[p[i]]=i,tr[i].insert(p[i]);
	dsu::init();
	for(int i=1; i<=m; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		merge(x,y);
	}
	scanf("%d",&q);
	for(int i=1; i<=q; ++i) {
		char op;
		int x,y;
		scanf(" %c %d %d\n",&op,&x,&y);
		if(op=='Q') {
			int ans=tr[dsu::find(x)][y];
			printf("%d\n",ans==-1?-1:v[ans]);
		} else
			merge(x,y);
	}
	return 0;
}