#include <cstdio>
#include <cstring>
using namespace std;
using ll = long long;
const int N = 1e3, M = 1e3, P = 123456789;
int n,m,a[N + 2];
char s[N + 2];
ll f[N + 2][M + 2][2];
int main() {
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	scanf("%s%d",s,&m);
	n=strlen(s);
	for(int i=1; i<=n; ++i)
		a[i]=s[n-i]-'0';
	f[n+1][0][0]=1;
	for(int i=n; i>=1; --i)
		for(int j=0; j<m; ++j) {
			for(int k=0; k<10; ++k) {
				if(k<=a[i]) (f[i][(j+k)%m][k<a[i]]+=f[i+1][j][0])%=P;
				(f[i][(j+k)%m][1]+=f[i+1][j][1])%=P;
			}
		}
	printf("%lld",(f[1][0][0]+f[1][0][1]-1+P)%P);
	return 0;
}