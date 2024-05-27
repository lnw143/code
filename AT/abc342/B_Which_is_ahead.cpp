#include<cstdio>
using namespace std;
const int N = 1e2;
int n,p[N + 2],q,a,b;
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		scanf("%d",&a);
		p[a]=i;
	}
	scanf("%d",&q);
	for(int i=1; i<=q; ++i) {
		scanf("%d%d",&a,&b);
		printf("%d\n",p[a]<p[b]?a:b);
	}
	return 0;
}