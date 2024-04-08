#include<cstdio>
#include<cstring>
#include<cmath>
#include<complex>
using namespace std;
const int N = 1e6;
int n,m,a[N + 2],b[N + 2];
int read(int a[]) {
	static char s[N + 2];
	scanf("%s",s+1);
	for(int i=1; s[i]; ++i)
		a[i]=s[i]-'0';
	return strlen(s+1);
}
int main() {
	n=read(a);
	m=read(b);
	
	return 0;
}