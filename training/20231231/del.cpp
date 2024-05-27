#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1e6 + 2;
int n,k,i,a[N],q[N],h,t,ans=1e9;
#define val(x) (a[(x)+1]-a[x])
void push(int x) {
	while(h<=t&&val(q[t])>=val(x)) --t;
	q[++t]=x;
}
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') f=-1;
		ch=getchar();
	}
	do {
		x=x*10+(ch^'0');
		ch=getchar();
	} while(ch>='0'&&ch<='9');
	return x*f;
}
int main() {
	n=read(),k=read();
	k=n-k;
	for(i=1; i<=n; ++i)
		a[i]=read();
	stable_sort(a+1,a+n+1);
	h=1;
	for(i=1; i<k-1; ++i)
		push(i);
	for(i=k; i<=n; ++i) {
		push(i-1);
		while(h<=t&&q[h]<=i-k) ++h;
		ans=min(ans,a[i]-a[i-k+1]+val(q[h]));
	}
	printf("%d",ans);
	return 0;
}