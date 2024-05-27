#include<cstdio>
#include<cstring>
using namespace std;
const int N = 100;
int n;
char s[N + 2];
int main() {
	scanf("%s",s);
	n=strlen(s);
	if(s[0]!='<'||s[n-1]!='>') return printf("No"),0;
	for(int i=1; i<n-1; ++i)
		if(s[i]!='=')
			return printf("No"),0;
	printf("Yes");
	return 0;
}