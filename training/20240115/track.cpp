#include<cstdio>
#include<set>
using namespace std;
const int N = 5e4;
int n,m,i,em,e[N * 2 + 2],ls[N + 2],nx[N * 2 + 2],cs[N * 2 + 2];
void insert(int x,int y,int z) {
	e[++em]=y;
	nx[em]=ls[x];
	cs[em]=z;
	ls[x]=em;
}
int len;
struct Node {
	int l,s;
};
Node wk(multiset<int> a) {
	Node r{0,0};
	while(!a.empty()) {
		auto it=a.begin();
		int eg=*it;
		a.erase(it);
		it=a.lower_bound(len-eg);
		if(it!=a.end()) {
			++r.s;
			a.erase(it);
		} else
			r.l=eg;
	}
	return r;
}
Node dfs(int x,int fa) {
	multiset<int> a;
	int sum=0;
	for(int i=ls[x]; i; i=nx[i])
		if(e[i]!=fa) {
			Node r=dfs(e[i],x);
			sum+=r.s;
			if(r.l+cs[i]>=len) ++sum;
			else a.insert(r.l+cs[i]);
		}
	Node r=wk(a);
	r.s+=sum;
	return r;
}
int bin_ans(int r) {
	int l=1;
	while(l<=r) {
		len=(l+r)/2;
		if(dfs(1,-1).s>=m) l=len+1;
		else r=len-1;
	}
	return l-1;
}
namespace Diameter {
	int maxd,maxv;
	void dfs(int x,int fa,int dep) {
		if(dep>maxd) maxd=dep,maxv=x;
		for(int i=ls[x]; i; i=nx[i])
			if(e[i]!=fa)
				dfs(e[i],x,dep+cs[i]);
	}
	int find_d() {
		maxd=0,maxv=-1;
		dfs(1,-1,0);
		maxd=0;
		dfs(maxv,-1,0);
		return maxd;
	}
}
int main() {
	freopen("track.in","r",stdin);
	freopen("track.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1; i<n; ++i) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		insert(u,v,w);
		insert(v,u,w);
	}
	printf("%d",bin_ans(Diameter::find_d()));
	return 0;
}