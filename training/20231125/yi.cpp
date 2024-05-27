#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1e5 + 2;
int n,nn,m,k,i,a[N],f;
bool cmp(int x,int y) {
	return x>y;
}
int main() {
	scanf("%d%d%d",&n,&m,&k);
	for(i=1; i<=n; ++i) {
		scanf("%d%d",&a[++nn],&f);
		if(f<2*k) --nn;
	}
	stable_sort(a+1,a+nn+1,cmp);
	for(i=1; i<=nn&&m>0; ++i)
		m-=a[i];
	printf("%d",m>0?-1:i-1);
	return 0;
}
