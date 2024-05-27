#include<cstdio>
#include<cstring>
using namespace std;
const int N = 2e2 + 2, M = N * 10, P = 1e9 + 9;
int n,m,i,f[N][M][2],g[N][M][2],ans;
char a[N],b[N];
void work(int n,char a[N],int f[N][M][2]) {
	for(int i=0; i<=a[1]-'0'; ++i)
		f[1][i][i<a[1]-'0']=1;
	for(int i=2; i<=n; ++i)
		for(int j=0; j<=9*i; ++j)
			for(int k=0; k<10&&k<=j; ++k) {
				(f[i][j][1]+=f[i-1][j-k][1])%=P;
				if(k==a[i]-'0')
					(f[i][j][0]+=f[i-1][j-k][0])%=P;
				else if(k<a[i]-'0')
					(f[i][j][1]+=f[i-1][j-k][0])%=P;
			}
	return ;
}
int main() {
	freopen("holiday.in","r",stdin);
	freopen("holiday.out","w",stdout);
	scanf("%s%s",a+1,b+1);
	n=strlen(a+1),m=strlen(b+1);
	work(n,a,f);
	work(m,b,g);
	for(i=1; i<=n*9&&i<=m*9; ++i)
		ans=(ans+(long long)((f[n][i][0]+f[n][i][1])%P)*((g[m][i][0]+g[m][i][1])%P)%P)%P;
	printf("%d",ans);
	return 0;
}