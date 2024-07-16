#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e5, M = 1e5, P = 998244353;
int n,m,a[N + 2],b[M + 2],mxa,mxb;
int main() {
	freopen("map.in","r",stdin);
	freopen("map.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	for(int i=1; i<=m; ++i) scanf("%d",&b[i]);
	mxa=*max_element(a+1,a+n+1);
	mxb=*max_element(b+1,b+m+1);
	if(mxa!=mxb) return printf("0"), 0;
	
	return 0;
}