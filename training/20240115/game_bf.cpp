#include<cstdio>
using namespace std;
const int P = 1e9 + 7, N = 7;
int n,m,a[N + 2][N + 2],b[(1 << (N * 2 - 1)) + 2],cnt,ans;
bool bz[1<<11];
void dfs2(int x,int y,int s) {
	if(y>m||x>n) return ;
	s=s<<1|a[x][y];
	if(x==n&&y==m) {
		b[++cnt]=s;
		return ;
	}
	dfs2(x+1,y,s);
	dfs2(x,y+1,s);
}
bool ck() {
	for(int i=1; i<cnt; ++i)
		if(b[i]<b[i+1])
			return false;
	// int s=0;
	// for(int i=1; i<=4; ++i)
	// 	for(int j=1; j+i<=5; ++j)
	// 		s=s<<1|a[i][j];
	// if(!bz[s]) {
	// 	bz[s]=true;
	// 	for(int i=1; i<=4; ++i)
	// 		for(int j=1; j+i<=5; ++j)
	// 			printf("%d%c",a[i][j]," \n"[j+i==5]);
	// }
	// for(int i=1; i<=n; ++i)
	// 	for(int j=1; j<=m; ++j)
	// 		// if(i+j<=5) printf(" %c"," \n"[j==m]);
	// 		printf("%d%c",a[i][j]," \n"[j==m]);
	return true;
}
void dfs(int x,int y) {
	if(y>m)
		++x,y=1;
	if(x>n) {
		cnt=0;
		dfs2(1,1,0);
		(ans+=ck())%=P;
		return ;
	}
	a[x][y]=0;
	dfs(x,y+1);
	a[x][y]=1;
	dfs(x,y+1);
}
int Ans(int n,int m) {
	ans=0;
	dfs(1,1);
	return ans;
}
int main() {
	// freopen(".out","w",stdout);
	scanf("%d%d",&n,&m);
	printf("%d",Ans(n,m));
	return 0;
}