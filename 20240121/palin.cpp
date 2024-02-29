#include<cstdio>
#include<cstring>
using namespace std;
const int N = 5e5;
int T,n,a[N * 2 + 2],f[N + 2],p[N * 2 + 2],i,cnt;
char c[N + 2],d[N + 2];
bool dfs(int l,int r,int L,int R) {
	if(L<l||r<R) return false;
	if(l==L&&r==R) {
		cnt=n;
		return true;
	}
	if(l<L&&p[l]==L-1||R<r&&p[l]==R+1) {
		if(l<L&&p[l]==L-1&&dfs(l+1,r,L-1,R)||R<r&&p[l]==R+1&&dfs(l+1,r,L,R+1)) {
			c[cnt]='L';
			d[cnt]=p[l]==L-1?'L':'R';
			--cnt;
			return true;
		}
		return false;
	}
	if(l<L&&p[r]==L-1||R<r&&p[r]==R+1) {
		if(l<L&&p[r]==L-1&&dfs(l,r-1,L-1,R)||R<r&&p[r]==R+1&&dfs(l,r-1,L,R+1)) {
			c[cnt]='R';
			d[cnt]=p[r]==L-1?'L':'R';
			--cnt;
			return true;
		}
		return false;
	}
	return false;
}
int read() {
	int x=0;
	char ch=getchar();
	while(ch<'0'&&ch>'9') ch=getchar();
	do {
		x=(x<<1)+(x<<3)+(ch^'0');
		ch=getchar();
	} while(ch>='0'&&ch<='9');
	return x;
}
int main() {
	freopen("palin.in","r",stdin);
	freopen("palin.out","w",stdout);
	T=read();
	while(T--) {
		n=read();
		memset(f,0,sizeof(f));
		for(i=1; i<=n*2; ++i) {
			a[i]=read();
			if(f[a[i]])
				p[f[a[i]]]=i,p[i]=f[a[i]];
			else
				f[a[i]]=i;
		}
		if(dfs(2,n*2,p[1],p[1])) {
			c[1]=d[1]='L';
			for(i=1; i<=n; ++i)
				putchar(c[i]);
			for(i=n; i>=1; --i)
				putchar(d[i]);
			putchar('\n');
		} else if(dfs(1,n*2-1,p[n*2],p[n*2])) {
			c[1]='R';
			d[1]='L';
			for(i=1; i<=n; ++i)
				putchar(c[i]);
			for(i=n; i>=1; --i)
				putchar(d[i]);
			putchar('\n');
		} else
			printf("-1\n");
	}
	return 0;
}
