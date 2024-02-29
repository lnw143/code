#include<cstdio>
using namespace std;
const int N = 2.5e5 + 2;
int n,a[N],p,f[N],i;
long long v[N];
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	f[1]=1;
	v[1]=a[1];
	for(i=2; i<=n; ++i) {
		scanf("%d",&p);
		f[i]=f[p]+1;
		v[f[i]]+=a[i];
	}
	for(i=n; i>=1; --i)
		if(v[i]<0) {
			putchar('-');
			return 0;
		} else if(v[i]>0) {
			putchar('+');
			return 0;
		}
	putchar('0');
	return 0;
}