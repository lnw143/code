#include<cstdio>
#include<vector>
using namespace std;
const int N = 2e5 + 2, inf = 1<<30;
int n,m,i,j,k,ans=inf;
int main() {
	scanf("%d%d%d",&n,&m,&k);
	vector<char> s[n + 2];
	for(i=1; i<=n; ++i) {
		s[i].reserve(m + 2);
		for(j=1; j<=m; ++j)
			scanf(" %c",&s[i][j]);
	}
	for(i=1; i<=n; ++i) {
		vector<int> u(m + 2),v(m + 2);
		for(j=1; j<=m; ++j) {
			u[j]=u[j-1],v[j]=v[j-1];
			if(s[i][j]=='x') ++u[j];
			else if(s[i][j]=='o') ++v[j];
			if(j>=k&&u[j]-u[j-k]==0)
				ans=min(ans,k-v[j]+v[j-k]);
		}
	}
	for(i=1; i<=m; ++i) {
		vector<int> u(n + 2),v(n + 2);
		for(j=1; j<=n; ++j) {
			u[j]=u[j-1],v[j]=v[j-1];
			if(s[j][i]=='x') ++u[j];
			else if(s[j][i]=='o') ++v[j];
			if(j>=k&&u[j]-u[j-k]==0)
				ans=min(ans,k-v[j]+v[j-k]);
		}
	}
	printf("%d",ans==inf?-1:ans);
	return 0;
}