#include<cstdio>
#include<cstring>
using namespace std;
const int N = 100, S = 100, T = 1e6;
int n,m,i,p[S + 2],stk[S + 2],tp;
char s[S + 2],t[T + 2];
bool f[2][S + 2];
void work() {
	for(int i=2; i<=m+1; ++i)
		f[0][i]=false;
	f[0][0]=true;
	for(int i=1; t[i]; ++i) {
		memset(f[i&1],0,sizeof(f[i&1]));
		for(int j=1; j<=m; ++j) {
			f[i&1][j]=f[i&1^1][j-1]&&(s[j]=='*'||s[j]=='?'||s[j]==t[i])||
			          f[i&1^1][j]&&(s[j]=='*')||
			          f[i&1][j-1]&&(s[j]=='['||s[j]==']'||s[j]=='*')||
			          f[i&1][p[j]]&&s[j]==']';
		}
		putchar(f[i&1][m]^'0');
	}
	putchar('\n');
}
int main() {
	freopen("walking.in","r",stdin);
	freopen("walking.out","w",stdout);
	scanf("%s%d",s+1,&n);
	m=strlen(s+1);
	for(i=1; i<=m; ++i)
		if(s[i]=='[')
			stk[++tp]=i;
		else if(s[i]==']')
			p[i]=stk[tp--];
	for(i=1; i<=n; ++i) {
		scanf("%s",t+1);
		work();
	}
	return 0;
}