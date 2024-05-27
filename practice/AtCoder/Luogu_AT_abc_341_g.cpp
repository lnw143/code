#include<cstdio>
using namespace std;
using ll = long long;
using db = double;
const int N(1e6);
int n,a[N + 2],stk[N + 2],tp;
ll s[N + 2];
db ans[N + 2];
db slope(int x,int y) {
	return db(s[y]-s[x])/(y-x);
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
	for(int i=n; i>=0; --i) {
		while(tp>1&&slope(stk[tp],stk[tp-1])>=slope(i,stk[tp])) --tp;
		ans[i+1]=slope(i,stk[tp]);
		stk[++tp]=i;
	}
	for(int i=1; i<=n; ++i)
		printf("%.8lf\n",ans[i]);
	return 0;
}