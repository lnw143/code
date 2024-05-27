#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,i,j,a[7][7],b[7][7],r[7],c[7],ans=-1;
bool br[7],bc[7];
void ck() {
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(a[i][j]!=b[r[i]][c[j]])
				return ;
	int s=0;
	for(int i=1; i<=n; ++i)
		a[0][i]=r[i];
	for(int i=1; i<n; ++i)
		for(int j=1; j<=n-i; ++j)
			if(r[j]>r[j+1]) {
				swap(r[j],r[j+1]);
				++s;
			}
	for(int i=1; i<=n; ++i)
		r[i]=a[0][i];
	for(int i=1; i<=m; ++i)
		b[0][i]=c[i];
	for(int i=1; i<m; ++i)
		for(int j=1; j<=m-i; ++j)
			if(c[j]>c[j+1]) {
				swap(c[j],c[j+1]);
				++s;
			}
	for(int i=1; i<=m; ++i)
		c[i]=b[0][i];
	if(ans==-1||s<ans) ans=s;
}
void dfsc(int x) {
	if(x>m) ck();
	for(int i=1; i<=m; ++i)
		if(!bc[i]) {
			bc[i]=true;
			c[x]=i;
			dfsc(x+1);
			bc[i]=false;
		}
}
void dfsr(int x) {
	if(x>n) dfsc(1);
	for(int i=1; i<=n; ++i)
		if(!br[i]) {
			br[i]=true;
			r[x]=i;
			dfsr(x+1);
			br[i]=false;
		}
}
int main() {
	scanf("%d%d",&n,&m);
	for(i=1; i<=n; ++i)
		for(j=1; j<=m; ++j)
			scanf("%d",&a[i][j]);
	for(i=1; i<=n; ++i)
		for(j=1; j<=m; ++j)
			scanf("%d",&b[i][j]);
	dfsr(1);
	printf("%d",ans);
	return 0;
}