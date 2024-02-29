#include<cstdio>
using namespace std;
using ll = long long;
const int N = 70;
int n,i,p[N + 2];
bool bz[N + 2];
ll ans;
ll sqr(ll x) {
	return x*x;
}
#define ptr(a,b) ((a)?((a)->b):0)
struct Landmine {
	int p,q,r,s;
	Landmine *pre,*nxt;
	ll cost() {
		return sqr(ptr(pre,p)-q)+sqr(p-ptr(nxt,r))+sqr(ptr(nxt,p)-ptr(ptr(nxt,nxt),s));
	}
	void del() {
		if(pre!=nullptr) pre->nxt=nxt;
		if(nxt!=nullptr) nxt->pre=pre;
	}
	Landmine():p(0),q(0),r(0),s(0),pre(nullptr),nxt(nullptr) {}
} a[N + 2];
ll calc() {
	for(int i=2; i<=n; ++i)
		a[i].pre=&a[i-1];
	for(int i=1; i<n; ++i)
		a[i].nxt=&a[i+1];
	ll cost=0;
	for(int i=1; i<=n; ++i) {
		cost+=a[p[i]].cost();
		a[p[i]].del();
	}
	return cost;
}
template<typename T>T max(T a,T b) {
	return a<b?b:a;
}
void dfs(int x) {
	if(x>n) {
		ans=max(ans,calc());
		return ;
	}
	for(int i=1; i<=n; ++i)
		if(!bz[i]) {
			bz[i]=true;
			p[x]=i;
			dfs(x+1);
			bz[i]=false;
		}
}
int main() {
	freopen("landmine.in","r",stdin);
	freopen("landmine.ans","w",stdout);
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i].p);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i].q);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i].r);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i].s);
	dfs(1);
	printf("%lld",ans);
	return 0;
}