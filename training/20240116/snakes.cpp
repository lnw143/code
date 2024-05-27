#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int N = 1e6;
int T,n,i,j,tp;
struct Node {
	int x,v;
	bool operator<(const Node t) const {
		return v==t.v?x<t.x:v<t.v;
	}
	Node operator-(const Node t) const {
		return {x, v-t.v};
	}
} a[N + 2];
deque<Node> f,g;
Node maxp() {
	Node r;
	if(!f.empty()&&(g.empty()||g.front()<f.front())) r=f.front(),f.pop_front();
	else r=g.front(),g.pop_front();
	return r;
}
Node minp() {
	Node r;
	if(!f.empty()&&(g.empty()||f.back()<g.back())) r=f.back(),f.pop_back();
	else r=g.back(),g.pop_back();
	return r;
}
int main() {
	freopen("snakes.in","r",stdin);
	freopen("snakes.out","w",stdout);
	scanf("%d%d",&T,&n);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i].v),a[i].x=i;
	while(T--) {
		for(i=n; i>=1; --i)
			f.push_back(a[i]);
		tp=0;
		for(i=1; i<n; ++i) {
			Node mx=maxp(),mn=minp();
			mx=mx-mn;
			if((!f.empty()&&f.back()<mx)||(!g.empty()&&g.back()<mx)) {
				if(tp) break;
				g.push_back(mx);
			} else {
				if(!tp) tp=i;
				f.push_back(mx);
			}
		}
		i-=i==n;
		if(!tp) printf("1\n");
		else printf("%d\n",n-((i-tp)&1?tp:tp+1)+1);
		if(T) {
			int k;
			scanf("%d",&k);
			for(i=1; i<=k; ++i) {
				int x,y;
				scanf("%d%d",&x,&y);
				a[x].v=y;
			}
			f.clear();
			g.clear();
		}
	}
	return 0;
}