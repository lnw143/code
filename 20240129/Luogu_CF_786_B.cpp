#include<cstdio>
#include<vector>
#include<utility>
#include<queue>
#include<cstring>
#define X second
#define Y first
using namespace std;
const int N = 1e5, LOG_N = 17, S = 9 * N;
using ll = long long;
using pli = pair<ll,int>;
int n,m,s,i;
namespace Graph {
	int tot;
	ll dis[S + 2];
	struct Edge {
		int to,cost;
	};
	vector<Edge> e[S + 2];
	void insert(int x,int y,int z) {
		e[x].push_back({y,z});
	}
	namespace SegmentTree {
		int in[N << 2],out[N << 2];
#define ls (x<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
		void maketree(int x,int l,int r) {
			in[x]=++tot;
			out[x]=++tot;
			if(l==r) {
				insert(out[x],l,0);
				insert(l,in[x],0);
				return ;
			}
			int mid=(l+r)/2;
			maketree(li);
			maketree(ri);
			insert(out[x],out[ls],0);
			insert(out[x],out[rs],0);
			insert(in[ls],in[x],0);
			insert(in[rs],in[x],0);
		}
		void findnode(int x,int l,int r,int L,int R,int to,int cost,bool f) {
			if(r<L||R<l) return ;
			if(L<=l&&r<=R) {
				if(f) insert(in[x],to,cost);
				else insert(to,out[x],cost);
				return ;
			}
			int mid=(l+r)/2;
			findnode(li,L,R,to,cost,f);
			findnode(ri,L,R,to,cost,f);
		}
#undef ls
#undef rs
#undef li
#undef ri
	}
	void shortest_path(int s) {
		memset(dis,0x3f,sizeof(dis));
		dis[s]=0;
		priority_queue<pli,vector<pli>,greater<pli>> hp;
		hp.push(pli(0,s));
		for(int i=1; i<=tot&&!hp.empty(); ++i) {
			pli u=hp.top();
			hp.pop();
			while(!hp.empty()&&dis[u.X]!=u.Y) {
				u=hp.top();
				hp.pop();
			}
			if(dis[u.X]!=u.Y) return ;
			for(Edge eg : e[u.X]) {
				int v=eg.to;
				if(u.Y+eg.cost<dis[v]) {
					dis[v]=u.Y+eg.cost;
					hp.push(pli(dis[v],v));
				}
			}
		}
	}
}
int main() {
	scanf("%d%d%d",&n,&m,&s);
	using namespace Graph;
	tot=n;
	SegmentTree::maketree(1,1,n);
	for(i=1; i<=m; ++i) {
		static int op,v,u,l,r,w;
		scanf("%d",&op);
		if(op==1) {
			scanf("%d%d%d",&u,&v,&w);
			insert(u,v,w);
		} else {
			scanf("%d%d%d%d",&u,&l,&r,&w);
			SegmentTree::findnode(1,1,n,l,r,u,w,op!=2);
		}
	}
	shortest_path(s);
	for(i=1; i<=n; ++i)
		printf("%lld ",dis[i]==0x3f3f3f3f3f3f3f3fll?-1:dis[i]);
	return 0;
}