#include<cstdio>
using namespace std;
const int N = 15 + 2;
int n,m,i,j,k,w[N],sum[N];
double f[N][N];
double calc(int l,int r) {
	double avg=double(sum[r]-sum[l-1])/(r-l+1),var=0;
	for(int i=l; i<=r; ++i)
		var+=(w[i]-avg)*(w[i]-avg);
	return var/(r-l+1);
}
int main() {
	scanf("%d%d",&n,&m);
	for(i=1; i<=n; ++i) {
		scanf("%d",&w[i]);
		sum[i]=sum[i-1]+w[i];
		f[1][i]=calc(1,i);
	}
	for(i=2; i<=d; ++i)
		for(j=1; j<=n; ++j) {

		}
	return 0;
}