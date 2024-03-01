#include<cstdio>
using namespace std;
int n,i;
long long a[3]={1,1,1};
int main() {
	scanf("%d",&n);
	for(i=1; i<n; ++i) {
		if(a[0]<a[1]) a[0]=a[0]*10+1;
		else if(a[1]<a[2]) a[1]=a[1]*10+1,a[0]=1;
		else a[2]=a[2]*10+1,a[0]=a[1]=1;
	}
	printf("%lld",a[0]+a[1]+a[2]);
	return 0;
}