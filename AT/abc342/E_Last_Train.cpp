#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define NO "Unreachable\n"
using namespace std;
using ll = long long;
struct Edge {
	int l,d,k,c,to;
	void read() {
		scanf("%d%d%d%d",&l,&d,&k,&c);
	}
};
struct Node {
	int x;
	ll d;
	bool operator<(const Node t) const {
		return d<t.d;
	}
	Node(int x_,ll d_):x(x_),d(d_) {}
};
const int N = 2e5;
const ll inf(5e18);
int n,m;
ll dis[N + 2];
vector<Edge> e[N + 2];
void dij() {
	priority_queue<Node> hp;
	memset(dis,-1,sizeof(dis));
	dis[n]=inf;
	hp.push(Node(n,inf));
	while(!hp.empty()) {
		auto [u,cs]=hp.top();
		hp.pop();
		for(const auto& [l,d,k,c,v]:e[u]) {
			ll x=(cs-c-l)/d;
			if(x>=k) x=k-1;
			if(0<=x&&l+x*d>dis[v]) {
				dis[v]=l+x*d;
				hp.push(Node(v,dis[v]));
			}
		}
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i) {
		int u;
		Edge t;
		t.read();
		scanf("%d%d",&t.to,&u);
		e[u].push_back(t);
	}
	dij();
	for(int i=1; i<n; ++i)
		if(dis[i]==-1)
			printf(NO);
		else 
			printf("%lld\n",dis[i]);
	return 0;
}