#include<cstdio>
#include<algorithm>
#include<random>
#include<chrono>
#include<cmath>
using namespace std;
using ll = long long;
using db = double;
const int N = 70;
const db RND_MAX = pow(2,32), V = 0.92, TimeLimit = 900;
int n,i,p[N + 2];
mt19937 rnd(random_device{}());
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
	ans=max(ans,cost);
	return cost;
}
ll calc(int x,int y) {
	swap(p[x],p[y]);
	ll c=calc();
	swap(p[x],p[y]);
	return c;
}
db RND() {
	return rnd()/RND_MAX;
}
template<typename T>
T randint(T l,T r) {
	return uniform_int_distribution<T>(l,r)(rnd);
}
void Simulated_Annealing() {
	ll c=calc();
	db temp=1e18;
	while(temp>1e-18) {
		int x=randint(1,n),y=randint(1,n);
		ll c_=calc(x,y);
		if(c_>c||RND()<exp((c_-c)*V/temp)) {
			c=c_;
			swap(p[x],p[y]);
		}
		temp*=.999;
	}
}
auto start_time=chrono::steady_clock::now();
double running_time() {
	return chrono::duration<double,milli>(chrono::steady_clock::now()-start_time).count();
}
int main() {
	freopen("landmine.in","r",stdin);
	freopen("landmine.out","w",stdout);
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i].p);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i].q);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i].r);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i].s);
	for(i=1; i<=n; ++i)
		p[i]=i;
	while(running_time()<TimeLimit)
		Simulated_Annealing();
	printf("%lld",ans);
	return 0;
}