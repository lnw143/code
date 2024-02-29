#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
const int N = 1e5 + 2;
int n,m,l,i,j,a[N],b[N],c,d,v[N],ans;
set<int> s[N];
bool cmp(int x,int y) {
	return b[x]>b[y];
}
int main() {
	scanf("%d%d%d",&n,&m,&l);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	for(i=1; i<=m; ++i)
		scanf("%d",&b[i]);
	for(i=1; i<=l; ++i) {
		scanf("%d%d",&c,&d);
		s[c].insert(d);
	}
	for(i=1; i<=m; ++i)
		v[i]=i;
	stable_sort(v+1,v+m+1,cmp);
	for(i=1; i<=n; ++i)
		for(j=1; j<=n; ++j)
			if(s[i].find(v[j])==s[i].end()) {
				ans=max(ans,a[i]+b[v[j]]);
				break;
			}
	printf("%d",ans);
	return 0;
}