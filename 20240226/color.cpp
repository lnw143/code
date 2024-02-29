#include<cstdio>
#include<algorithm>
using namespace std;
using ll = long long;
const int N(20), M(1 << N);
int n,m,a[M + 2][2];
ll s[M + 2][2],f[M + 2];
int main() {
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	scanf("%d",&n);
	m=1<<n;
	for(int i=0; i<m; ++i)
		scanf("%d",&a[i][0]),s[i][0]=a[i][0];
	for(int i=0; i<m; ++i)
		scanf("%d",&a[i][1]),s[i][1]=a[i][1];
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			if(j&(1<<i))
				s[j][0]+=s[j^(1<<i)][0],
				s[j][1]+=s[j^(1<<i)][1];
	f[0]=min(a[0][0],a[0][1]);
	for(int i=1; i<m; ++i) {
		f[i]=1ll<<60;
		for(int j=0; j<n; ++j) 
			if(i&(1<<j))
				f[i]=min(f[i],f[i^(1<<j)]+min(s[i][0]-s[i^(1<<j)][0],s[i][1]-s[i^(1<<j)][1]));
	}
	printf("%lld",f[m-1]);
	return 0;
}