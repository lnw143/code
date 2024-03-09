#include<cstdio>
using namespace std;
const int N(1e2);
char s[N + 2];
int main() {
	scanf("%s",s);
	int t=0;
	for(int i=0; s[i]; ++i) {
		if(s[i]=='|') t^=1;
		else if(!t) putchar(s[i]);
	}
	return 0;
}