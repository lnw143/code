#include<cstdio>
#include<algorithm>
using namespace std;
const int N(6e2);
using ll = long long;
int n,p,a[N + 2][N + 2];
int det() {
	int sgn=0;
	for(int i=1; i<=n; ++i)
		for(int j=i+1; j<=n; ++j) {
			while(a[i][i]) {
				ll d=a[j][i]/a[i][i];
				for(int k=1; k<=n; ++k)
					a[j][k]=(a[j][k]-d*a[i][k]%p)%p;
				swap(a[i],a[j]);
				sgn^=1;
			}
			swap(a[i],a[j]);
			sgn^=1;
		}
	ll ans=sgn?-1:1;
	for(int i=1; i<=n; ++i) ans=ans*a[i][i]%p;
	return (ans+p)%p;
}
int main() {
	scanf("%d%d",&n,&p);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			scanf("%d",&a[i][j]);
	printf("%d",det());
	return 0;
}