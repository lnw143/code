#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
using ll = long long;
const int N = 1e6 + 2;
int n,i,sgn;
ll w[N],v,l,r,L,R,ctr,ans[N],d[N],sum,minn;
set<ll> st;
ll pos(ll x) {
	return sgn?ctr-x:x-ctr;    // 原数轴上的位置->相对于翻转后0的位置
}
ll val(ll x) {
	return sgn?ctr-x:ctr+x;   // 相对于翻转后0的位置->原数轴上的位置
}
ll res() {
	return l<=r?l:*st.begin();
}
//pos(val(x))=val(pos(x))=x
int main() {
	scanf("%d%lld",&n,&r);
	for(i=1; i<=n-2; ++i) {
		scanf("%lld",&w[i]);
		L=pos(0),R=pos(w[i]);
		if(L>R) swap(L,R);
		l=max(l,L),r=min(r,R);
		while(!st.empty()&&(*st.begin())<L) st.erase(st.begin());
		while(!st.empty()&&(*st.rbegin())>R) st.erase(*st.rbegin());
		if(st.empty()&&l>r) return printf("NO\n"),0;
		v=pos(w[i]);
		if(st.find(v)!=st.end()||(l<=v&&v<=r)) {
			l=0,r=w[i];
			ctr=sgn=0;
			st.clear();
			ans[i]=w[i];
		} else {
			ans[i]=val(res());
			ctr=w[i]-ctr;
			sgn^=1;
			st.insert(pos(w[i]));
		}
	}
	printf("YES\n");
	sgn=1;
	d[n-1]=val(res());
	for(i=n-2; i>=1; --i) {
		if(ans[i]==w[i]||d[i+1]==w[i])
			d[i]=ans[i];
		else d[i]=w[i]-d[i+1];
	}
	for(i=n-2; i>=1; --i) {
		if(abs(d[i])+abs(d[i+1])!=w[i]) sgn=-sgn;
		d[i]*=sgn;
	}
	for(i=1; i<n; ++i)
		d[i]+=d[i-1],minn=min(minn,d[i]);
	for(i=1; i<=n; ++i)
		printf("%lld ",d[i-1]-minn);
	return 0;
}