#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
const int N = 2e5 + 2;
int n,m,sum,a[N],b[N],i,f[N];
map<int,int> mp;
void dp(int val,int num) {
	if(!val) return ;
	if(val>0)
		for(int i=m; i>=val*num; --i)
			f[i]=min(f[i],f[i-val*num]+num);
	else
		for(int i=0; i<=m+val*num; ++i)
			f[i]=min(f[i],f[i-val*num]+num);
}
int main() {
	scanf("%d%d",&n,&m);
	for(i=1; i<=n; ++i) {
		scanf("%d%d",&a[i],&b[i]);
		sum+=a[i];
		++mp[b[i]-a[i]];
	}
	for(i=0; i<=m; ++i)
		f[i]=n+1;
	f[sum]=0;
	for(auto h : mp) if(h.first) {
			int v=h.first,w=h.second;
			for(i=1; i<=w; w-=i,i<<=1)
				dp(v,i);
			if(w) dp(v,w);
		}
	for(i=0; i<=m; ++i)
		printf("%d\n",f[i]<=n?f[i]:-1);
	return 0;
}