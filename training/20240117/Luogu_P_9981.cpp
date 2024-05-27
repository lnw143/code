#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
using ll = long long;
const int N = 2e5, M = 4e5;
int n,m,i,deg[N + 2],dis[N + 2],em,e[M + 2],ls[N + 2],nx[M + 2],cs[M + 2];
vector<int> v[N + 2];
void insert(int x,int y,int z) {
	e[++em]=y;
	nx[em]=ls[x];
	cs[em]=z;
	ls[x]=em;
}
void topu() {
	for(int i=1; i<=n; ++i)
		deg[i]=0;
	for(int i=1; i<=n; ++i)
		for(int j=ls[i]; j; j=nx[j])
			++deg[e[j]];
	queue<int> q;
	for(int i=1; i<=n; ++i)
		if(deg[i]==0)
			q.push(i);
	while(!q.empty()) {
		int u=q.front();
		v[dis[u]].push_back(u);
		q.pop();
		for(int i=ls[u]; i; i=nx[i]) {
			dis[e[i]]=dis[u]+1;
			if(--deg[e[i]]==0)
				q.push(e[i]);
		}
	}
}
struct Node {
	int pre,prerk;
	ll sum;
	bool operator==(const Node t) const {
		return pre==t.pre&&prerk==t.prerk;
	}
} a[N + 2];
bool cmp(int x,int y) {
	return a[x].pre!=a[y].pre?a[x].pre<a[y].pre:a[x].prerk<a[y].prerk;
}
int main() {
	scanf("%d%d",&n,&m);
	for(i=1; i<=m; ++i) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		insert(v,u,w);
	}
	topu();
	for(i=0; i<n; ++i) {
		if(v[i].size()==0) continue;
		stable_sort(v[i].begin(),v[i].end(),cmp);
		for(int j=0,p=0; j<v[i].size(); ++j) {
			int u=v[i][j];
			if(!(j>0&&a[u]==a[v[i][j-1]]))
				++p;
			for(int k=ls[u]; k; k=nx[k])
				if(dis[e[k]]==dis[u]+1&&(!a[e[k]].prerk||cs[k]<a[e[k]].pre)) {
					a[e[k]].prerk=p;
					a[e[k]].pre=cs[k];
					a[e[k]].sum=a[u].sum+cs[k];
				}
		}
	}
	for(i=1; i<=n; ++i)
		printf("%d %lld\n",dis[i],a[i].sum);
	return 0;
}