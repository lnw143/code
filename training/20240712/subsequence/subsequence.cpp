#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;
const int N = 3e5;
int n,p[N + 2],f[N + 2];
char s[N + 2];
map<int,int> a,b;
int main() {
	freopen("subsequence.in","r",stdin);
	freopen("subsequence.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&p[i]);
	scanf("%s",s+1);
	for(int i=1; i<=n; ++i) {
		auto x=a.upper_bound(-p[i]),y=b.upper_bound(p[i]);
		if(x!=a.end()) f[i]=max(f[i],x->second+1);
		if(y!=b.end()) f[i]=max(f[i],y->second+1);
		if(f[i]<n-1) {
			if(s[f[i]+1]=='U') {
				while(!a.empty()) {
					auto it=a.lower_bound(-p[i]);
					if(it==a.begin()) break;
					--it;
					if(it->second>f[i]) break;
					a.erase(it->first);
				}
				a[-p[i]]=f[i];
			} else {
				while(!b.empty()) {
					auto it=b.lower_bound(p[i]);
					if(it==b.begin()) break;
					--it;
					if(it->second>f[i]) break;
					b.erase(it->first);
				}
				b[p[i]]=f[i];
			}
		}
		// printf("%d\n",f[i]);
	}
	printf("%d",*max_element(f+1,f+n+1));
	return 0;
}