#include<cstdio>
#include<cmath>
#include<vector>
using namespace std;
using db = double;
const int N(1e5);
const db eps(1e-8), inf(1e20);
int n,ori,tar,a;
db sig(db x) {
	return x>0?1:x<0?-1:0;
}
struct Node {
	int pw,pt;
	void read() {
		scanf("%d%d",&pw,&pt);
	}
} w[N + 2];
namespace Graph {
	vector<int> e[N + 2];
	int fa[N + 2],ord[N + 2];
	void dfs(int x) {
		for(int y : e[x])
			if(y!=fa[x]) {
				fa[y]=x;
				dfs(y);
			}
		ord[++*ord]=x;
	}
	void read() {
		for(int i=1; i<n; ++i) {
			static int u,v;
			scanf("%d%d",&u,&v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		dfs(1);
	}
}
db trans(db power,db point,int t) {
	db x=power-w[t].pw,y=point-w[t].pt;
	return point+2*sig(x)*(sqrt(abs(x)+1)-1)-a*sig(y)*(sqrt(abs(y)+1)-1);
}
namespace TreeDP {
	using namespace Graph;
	struct Sol {
		int x;
		db y;
		bool operator>(const Sol t) const {
			return y>t.y;
		}
		Sol(int x_,db y_):x(x_),y(y_) {}
		Sol() {}
	};
	struct OptSol {
		Sol s[2];
		void upd(Sol x) {
			if(x>s[0]) s[1]=s[0],s[0]=x;
			else if(x>s[1]) s[1]=x;
		}
		db get(int x=-1) {
			return s[s[0].x==x].y;
		}
		void clear() {
			s[0].y=s[1].y=-inf;
		}
	} f[N + 2];
	bool check(db power) {
		for(int i=1; i<=n; ++i)
			f[i].clear();
		for(int x=1; x<=n; ++x)
			if(e[x].size()<=1)
				f[x].s[0]=Sol(x,trans(power,ori,x));
		for(int i=1; i<=n; ++i) {
			int u=ord[i];
			for(int v : e[u])
				if(v!=fa[u])
					f[u].upd(Sol(v,trans(power,f[v].get(u),u)));
		}
		for(int i=n; i>=1; --i) {
			int u=ord[i];
			for(int v : e[u])
				if(v!=fa[u])
					f[v].upd(Sol(u,trans(power,f[u].get(v),v)));
		}
		for(int x=1; x<=n; ++x)
			if(e[x].size()<=1&&f[x].s[0].y>=tar)
				return true;
		return false;
	}
}
db solve() {
	db l=0,r=inf,mid;
	while(l+eps<r) {
		mid=(l+r)/2;
		if(TreeDP::check(mid))
			r=mid;
		else l=mid;
	}
	return r;
}
int main() {
	freopen("pigeatyy.in","r",stdin);
	freopen("pigeatyy.out","w",stdout);
	scanf("%*d%d%d%d%d",&n,&ori,&tar,&a);
	Graph::read();
	for(int i=1; i<=n; ++i)
		w[i].read();
	printf("%.6lf",solve());
	return 0;
}