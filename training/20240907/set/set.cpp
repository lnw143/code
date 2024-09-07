#include <cstdio>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>
using namespace std;
const int N = 80;
int n,m,a[N + 2];
double ans=-1;
vector<int> e[N + 2],g[N + 2];
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
inline int randint(int l,int r) {
	return uniform_int_distribution<int>(l,r)(rnd);
}
inline double randpr() {
	return uniform_real_distribution<double>(0,1)(rnd);
}
struct state {
	bool s[N + 2];
	int sum,psum;
	void dfs(int u,bool goal) {
		if(s[u]==goal) return ;
		if(goal) sum+=a[u],psum+=a[u]*a[u];
		else sum-=a[u],psum-=a[u]*a[u];
		s[u]=goal;
		for(auto v : (goal?e[u]:g[u]))
			dfs(v,goal);
	}
	void random() {
		int x=randint(1,n);
		dfs(x,!s[x]);
		ans=max(ans,val());
	}
	double val() {
		if(!psum) return -1;
		return (double)sum*sum/psum;
	}
	state():sum(0),psum(0) {
		for(int i=1; i<=n; ++i) s[i]=false;
	}
};
void SA() {
	state x;
	x.random();
	for(double temp=1e7; temp>1e-7; temp*=0.9999) {
		state y=x;
		y.random();
		if(y.val()>x.val()||randpr()<exp((y.val()-x.val())/temp)) x=y;
	}
}
int main() {
	freopen("set.in","r",stdin);
	freopen("set.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	for(int i=1; i<=m; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		g[v].push_back(u);
	}
	SA();
	printf("%.8lf",ans);
	return 0;
}