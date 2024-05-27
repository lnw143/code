#include<cstdio>
using namespace std;
const int N = 1e2 + 2, M = 1e6 + 2, P = 114514;
using ll = long long;
int n,m,i,a[N],ans[M];
bool ck(int x) {
	int sum=0,x1=1;
	for(int i=0; i<=n; ++i,x1=(ll)x1*x%P)
		sum=(sum+(ll)x1*a[i]%P)%P;
	return sum==0;
}
int read() {
	ll x=0;
	int f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') f=-1;
		ch=getchar();
	}
	do {
		x=((x<<3)%P+(x<<1)%P+(ch^'0'))%P;
		ch=getchar();
	} while(ch>='0'&&ch<='9');
	return x*f;
}
int main() {
	scanf("%d%d",&n,&m);
	for(i=0; i<=n; ++i)
		a[i]=read();
	for(i=1; i<=m; ++i)
		if(ck(i))
			ans[++ans[0]]=i;
	printf("%d",ans[0]);
	for(i=1; i<=ans[0]; ++i)
		printf("\n%d",ans[i]);
	return 0;
}