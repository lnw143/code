#include<cstdio>
using namespace std;
const int N = 100;
char s[N + 2];
int main() {
	scanf("%s",s);
	for(int i=0; s[i+1]; ++i)
		if(s[i+1]-s[i]<0)
			return printf("No"),0;
	printf("Yes");
	return 0;
}