#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
using ll = __int128;
const int N = 1e5;
int n,m,i,j,d[N + 2],deg[N + 2];
vector<int> e[N + 2];
queue<int> q;
ll gcd(ll x,ll y) {
	ll r=x%y;
	while(r)
		x=y,y=r,r=x%y;
	return y;
}
struct Num {
	ll p,q;
	Num operator/(const ll x) const {
		return Num(p,q*x);
	}
	Num operator+(const Num t) const {
		const ll g=gcd(q,t.q);
		return Num(p*t.q/g+q*t.p/g,q*t.q/g);
	}
	Num& operator+=(const Num t) {
		return (*this)=(*this)+t;
	}
	Num(ll x):p(x),q(1) {}
	Num(ll x,ll y):p(x),q(y) {
		ll g=gcd(p,q);
		p/=g;
		q/=g;
	}
	Num():p(0),q(1) {}
} a[N + 2];
char buf[128];
void write(ll x) {
	int l=0;
	do
		buf[++l]=x%10;
	while(x/=10);
	while(l) putchar(buf[l--]^'0');
}
int main() {
	freopen("water.in","r",stdin);
	freopen("water.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1; i<=n; ++i) {
		int v;
		scanf("%d",&d[i]);
		e[i].reserve(d[i]);
		for(j=1; j<=d[i]; ++j)
			scanf("%d",&v),e[i].push_back(v),++deg[v];
	}
	for(i=1; i<=m; ++i)
		a[i]=1;
	for(i=1; i<=n; ++i)
		if(deg[i]==0)
			q.push(i);
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		for(int v : e[u]) {
			a[v]+=a[u]/d[u];
			if(--deg[v]==0)
				q.push(v);
		}
	}
	for(i=1; i<=n; ++i)
		if(d[i]==0)
			write(a[i].p),putchar(' '),write(a[i].q),putchar('\n');
	return 0;
}