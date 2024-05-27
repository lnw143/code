#include<cstdio>
#include<cmath>
#include<random>
using namespace std;
mt19937 rnd(random_device{}());
uniform_int_distribution<int> d(0,1e8);
const int N(20), M(N * (N - 1) / 2);
int n,m,p[N + 2][N + 2],a[M + 2],b[M + 2];
double dis(int v) {
	double sum=0;
	for(int i=1; i<=n; ++i)
		sum+=double(p[a[v]][i]-p[b[v]][i])*(p[a[v]][i]-p[b[v]][i]);
	return sqrt(sum);
}
int main() {
	scanf("%d",&n);
	m=n*(n-1)/2;
	for(int i=1; i<=m; ++i)
		scanf("%d%d",&a[i],&b[i]);
	while(true) {
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=n; ++j)
				p[i][j]=d(rnd);
		bool flag=true;
		for(int i=1; i<m; ++i)
			if(dis(i)>=dis(i+1))
				flag=false;
		if(flag) break;
	}
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			printf("%d%c",p[i][j]," \n"[j==n]);
	return 0;
}