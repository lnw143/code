#include<cstdio>
using namespace std;
const int N = 100;
int i,m;
char s[N + 2],ans[N + 2];
int main() {
	scanf("%s",s);
	for(i=0; s[i]; ++i)
		if(s[i]=='.')
			m=0;
		else
			ans[m++]=s[i];
	for(i=0; i<m; ++i)
		putchar(ans[i]);
	return 0;
}