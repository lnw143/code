#include<cstdio>
using namespace std;
const int N = 1e5 + 2;
int n,k,a[N],r[N],i;
long long ans;
void msort(int x,int y) {
	if(x>=y) return ;
	int md=(x+y)/2,i=x,j=md+1,k=x;
	msort(x,md);
	msort(md+1,y);
	while(i<=md&&j<=y)
		if(a[i]<=a[j])
			r[k++]=a[i++];
		else {
			r[k++]=a[j++];
			ans+=md-i+1;
		}
	while(i<=md) r[k++]=a[i++];
	while(j<=y) r[k++]=a[j++];
	for(i=x; i<=y; ++i)
		a[i]=r[i];
}
int main() {
	scanf("%d%d",&n,&k);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	msort(1,n);
	printf("%lld",ans>k?ans-k:0);
	return 0;
}
