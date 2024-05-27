#include<cstdio>
#include<cstring>
using namespace std;
const int N(1e5);
int T;
char s[N + 2];
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%s",s);
		printf(s[strlen(s)-1]=='0'?"E\n":"B\n");
	}
	return 0;
}