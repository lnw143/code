#include<cstdio>
using namespace std;
int n,m,i,j;
char ch;
int main() {
	freopen("bw.in","r",stdin);
	freopen("bw.out","w",stdout);
	scanf("%d%d %c",&n,&m,&ch);
	for(i=1; i<=m; ++i) {
		for(j=1; j<=n; ++j)
			if((i+j)%2)
				putchar(ch=='B'?'W':'B');
			else
				putchar(ch);
		putchar('\n');
	}
	return 0;
}