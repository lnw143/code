#include<cstdio>
#include<vector>
using namespace std;
int n,m,i,j,ans;
vector<int> a[9];
char s[9];
int lg2(int x) {
	int r=0;
	while(x) {
		++r;
		x>>=1;
	}
	return r;
}
int main() {
	scanf("%d",&n);
	m=lg2(n-1);
	for(i=1; i<n; ++i)
		for(j=0; j<m; ++j)
			if(i&(1<<j))
				a[j].push_back(i);
	printf("%d\n",m);
	for(i=0; i<m; ++i) {
		printf("%d ",a[i].size());
		for(int j : a[i])
			printf("%d ",j);
		putchar('\n');
	}
	fflush(stdout);
	scanf("%s",s);
	for(i=0; s[i]; ++i)
		if(s[i]=='1')
			ans|=1<<i;
	printf("%d",ans==0?n:ans);
	fflush(stdout);
	return 0;
}