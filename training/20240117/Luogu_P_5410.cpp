#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
using ll = long long;
const int N = 2e7;
int n,m,i,z[N * 2 + 3],l,r;
ll p,q;
char a[N + 2],b[N + 2],s[N * 2 + 3];
int main() {
	scanf("%s%s",a+1,b+1);
	n=strlen(a+1);
	m=strlen(b+1);
	for(i=1; i<=m; ++i)
		s[i]=b[i];
	s[m+1]=-1;
	for(i=1; i<=n; ++i)
		s[i+1+m]=a[i];
	z[1]=m;
	l=1,r=0;
	n+=m+1;
	for(i=2; i<=n; ++i) {
		if(i<=r&&z[i-l+1]<r-i+1)
			z[i]=z[i-l+1];
		else {
			z[i]=max(r-i+1,0);
			while(i+z[i]<=n&&s[z[i]+1]==s[i+z[i]])
				++z[i];
		}
		if(i+z[i]-1>r) l=i,r=i+z[i]-1;
	}
	for(i=1; i<=m; ++i)
		p^=i*ll(z[i]+1);
	for(i=m+2; i<=n; ++i)
		q^=ll(i-m-1)*(z[i]+1);
	printf("%lld\n%lld",p,q);
	return 0;
}