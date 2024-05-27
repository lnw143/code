#include<cstdio>
using namespace std;
const int N = 1e2 + 2;
int n,i;
char ch[N];
int main() {
	scanf("%d%s",&n,ch+1);
	for(i=1; i<n; ++i)
		if(ch[i]=='a'&&ch[i+1]=='b'||ch[i]=='b'&&ch[i+1]=='a') {
			printf("Yes");
			return 0;
		}
	printf("No");
	return 0;
}