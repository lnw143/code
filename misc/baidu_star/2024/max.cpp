#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>
using namespace std;
using ll = long long;
const int N = 1e6;
int T,n;
ll a[N + 2];
int main() {
	// freopen(".in","r",stdin);
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(int i=1; i<=n; ++i)
			scanf("%lld",&a[i]);
		vector<int> p,q,w;
		int zero=0;
		for(int i=1; i<=n; ++i)
			if(a[i]<0)
				p.push_back(-a[i]);
			else if(a[i]>0)
				q.push_back(a[i]);
			else
				++zero;
		assert(p.size()+q.size()+zero==n);
		if(n==1||zero==n) {
			printf("0\n");
			continue;
		}
		sort(p.begin(),p.end());
		sort(q.begin(),q.end());
		if(p.size()==0) {
			if(q.size()==1) {
				printf("%lld\n",zero>1?2ll*q[0]:q[0]);
				continue;
			}
			if(zero==0) {
				ll ans=0;
				for(int i=1; i<q.size(); ++i)
					ans+=q[i];
				if(q.size()>2) ans+=q.back();
				printf("%lld\n",ans-q[0]);
				continue;
			} else {
				ll ans=0;
				for(auto i : q)
					ans+=i;
				printf("%lld\n",ans+q.back());
				continue;
			}
		}
		if(q.size()==0) {
			if(p.size()==1) {
				printf("%lld\n",zero>1?2ll*p[0]:p[0]);
				continue;
			}
			if(zero==0) {
				ll ans=0;
				for(int i=1; i<p.size(); ++i)
					ans+=p[i];
				if(p.size()>2) ans+=p.back();
				printf("%lld\n",ans-p[0]);
				continue;
			} else {
				ll ans=0;
				for(auto i : p)
					ans+=i;
				printf("%lld\n",ans+p.back());
				continue;
			}
		}
		ll ans=p.back()+q.back();
		if(q.size()>1)
			for(auto i : q)
				ans+=i;
		else if(q.size()==1)
			w.push_back(q[0]);
		if(p.size()>1)
			for(auto i : p)
				ans+=i;
		else if(p.size()==1)
			w.push_back(p[0]);
		sort(w.begin(),w.end(),greater<int>());
		for(int i=0; i<w.size(); ++i)
			if(i<zero)
				ans+=w[i];
		assert(ans>0);
		printf("%lld\n",ans);
	}
	return 0;
}