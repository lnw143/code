#include <cstdio>
#include <chrono>
#include <ext/random>
#include <algorithm>
using namespace std;
const int N = 3e5, K = 100;
int n,q,B,a[N + 2],cnt[N + 2],ans[N + 2];
struct query {
	int l,r,k,id;
} qr[N + 2];
__gnu_cxx::sfmt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
int main() {
	scanf("%d%d",&n,&q);
	B=n/sqrt(q);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	for(int i=1; i<=q; ++i) scanf("%d%d%d",&qr[i].l,&qr[i].r,&qr[i].k),qr[i].id=i;
	sort(qr+1,qr+q+1,[](auto x,auto y) {
		return x.l/B!=y.l/B?x.l/B<y.l/B:(x.r==y.r?false:((x.l/B)&1)^(x.r<y.r));
	});
	for(int i=1,l=1,r=0; i<=q; ++i) {
		auto x=qr[i];
		while(r<x.r) ++cnt[a[++r]];
		while(x.l<l) ++cnt[a[--l]];
		while(x.r<r) --cnt[a[r--]];
		while(l<x.l) --cnt[a[l++]];
		int &Ans=ans[x.id];
		Ans=1e9;
		for(int j=1; j<=K; ++j) {
			int p=uniform_int_distribution<int>(x.l,x.r)(rnd);
			if(cnt[a[p]]*x.k>r-l+1) Ans=min(Ans,a[p]);
		}
		if(Ans==1e9) Ans=-1;
	}
	for(int i=1; i<=q; ++i) printf("%d\n",ans[i]);
	return 0;
}