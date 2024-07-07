#include <cstdio>
#include <vector>
#include <bitset>
using namespace std;
const int N = 1e3, L = 1e3;
int n,m,l,c[N + 2],v[N + 2];
bitset<L + 2> f[N + 2],ans;
int main() {
	freopen("bag.in","r",stdin);
	freopen("bag.out","w",stdout);
	scanf("%d%d",&n,&l);
	f[0][0]=1;
	for(int i=1; i<=n; ++i) {
		int c,v;
		scanf("%d%d",&c,&v);
		vector<int> t;
		for(int j=1; ; j<<=1) {
			if(j>c) {
				t.push_back(c-(j>>1));
				break;
			} else t.push_back(j);
			if(j==c) break;
		}
		for(int j=n; j>=1; --j) {
			bitset<L + 2> cur;
			for(auto k : t)
				if(k*v<=l)
					cur|=(cur|f[j-1])<<k*v;
			f[j]|=cur;
		}
	}
	scanf("%d",&m);
	for(int i=1; i<=m; ++i) {
		int x;
		scanf("%d",&x);
		ans|=f[x];
	}
	for(int i=1; i<=l; ++i)
		ans[i]&&printf("%d ",i);
	return 0;
}