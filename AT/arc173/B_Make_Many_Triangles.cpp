#include<cstdio>
#include<random>
#include<chrono>
#include<algorithm>
using namespace std;
using db = double;
const db eps(1e-12), TL(1.8);
const int N(300);
mt19937 rnd(random_device{}());
struct Point {
	int x,y;
	void read() {
		scanf("%d%d",&x,&y);
	}
} a[N + 2];
auto st=chrono::steady_clock::now();
int n,ans,p[N + 2];
db runt() {
	return chrono::duration<db>(chrono::steady_clock::now()-st).count();
}
db zero(db x) {
	return x<-eps||x>eps;
}
void solve() {
	for(int i=1; i<=n; ++i)
		p[i]=i;
	for(int i=1; i<=n; ++i)
		swap(p[i],p[rnd()%i+1]);
	int sum=0;
	for(int i=1; i+2<=n; i+=3) {
		Point &x=a[p[i]],&y=a[p[i+1]],&z=a[p[i+2]];
		if(x.x==y.x) {
			sum+=(y.x!=z.x);
			continue;
		}
		db k=(db)(y.y-x.y)/(y.x-x.x),b=x.y-k*x.x;
		if(zero(k*z.x+b-z.y)) ++sum;
	}
	ans=max(ans,sum);
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		a[i].read();
	while(runt()<TL) solve();
	printf("%d",ans);
	return 0;
}