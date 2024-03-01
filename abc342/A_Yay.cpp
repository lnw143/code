#include<cstdio>
using namespace std;
const int N = 1e2, A = 26;
int i,p[A + 2],t[A + 2];
char s[N + 2];
int main() {
	scanf("%s",&s);
	for(int i=0; s[i]; ++i)
		++t[s[i]-'a'],p[s[i]-'a']=i;
	for(int i=0; i<A; ++i)
		if(t[i]==1)
			printf("%d",p[i]+1);
	return 0;
}