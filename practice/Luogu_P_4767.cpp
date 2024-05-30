#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 3e3;
int n,m,a[N + 2];
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	
	return 0;
}