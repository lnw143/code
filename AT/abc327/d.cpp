#include<cstdio>
using namespace std;
const int N = 2e5 + 2;
int n,m,i,a[N],b[N],fa[N*2];
int find(int x) {
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main() {
	scanf("%d%d",&n,&m);
	for(i=1; i<=2*n; ++i)
		fa[i]=i;
	for(i=1; i<=m; ++i)
		scanf("%d",&a[i]);
	for(i=1; i<=m; ++i)
		scanf("%d",&b[i]);
	for(i=1; i<=m; ++i) {
		if(find(a[i])==find(b[i])) {
			printf("No");
			return 0;
		}
		fa[find(a[i])]=find(b[i]+n);
		fa[find(b[i])]=find(a[i]+n);
	}
	printf("Yes");
	return 0;
}