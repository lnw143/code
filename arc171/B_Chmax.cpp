#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;
const int N = 2e5, P = 998244353;
int n,x,i,j;
ll ans=1;
bool bz[N + 2];
vector<int> a,b;
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i) {
		scanf("%d",&x);
		if(bz[i]&&i!=x||x<i) {
			printf("0");
			return 0;
		}
		if(!bz[x]) {
			bz[x]=true;
			a.push_back(i);
			b.push_back(x);
		}
	}
	stable_sort(b.begin(),b.end());
	for(i=j=0; i<b.size(); ++i) {
		while(j<a.size()&&a[j]<=b[i]) ++j;
		(ans*=j-i)%=P;
	}
	printf("%lld",ans);
	return 0;
}