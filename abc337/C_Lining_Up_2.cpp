#include<cstdio>
using namespace std;
const int N = 3e5;
int n,i,a[N + 2],b[N + 2];
void dfs(int x) {
	if(!x) return ;
	printf("%d ",x);
	dfs(b[x]);
}
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
		if(~a[i])
			b[a[i]]=i;
	}
	for(i=1; i<=n; ++i)
		if(a[i]==-1)
			dfs(i);
	return 0;
}