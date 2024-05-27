#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1e7 + 2;
int n,i,a[N],minn=1,maxn=0,ans=1;
inline int read() {
	char ch=getchar();
	int x=0;
	while(ch<'0'||ch>'9')
		ch=getchar();
	do {
		x=(x<<3)+(x<<1)+(ch^'0');
		ch=getchar();
	} while(ch>='0'&&ch<='9');
	return x;
}
int main() {
	n=read();
	for(i=1; i<=n; ++i)
		a[i]=read();
	for(i=2; i<=n; ++i) {
		if(a[i]<a[minn]) {
			minn=i;
			maxn=a[i];
			continue;
		}
		if(a[i]>=maxn) {
			maxn=a[i];
			ans=max(ans,i-minn+1);
		}
	}
	printf("%d",ans);
	return 0;
}