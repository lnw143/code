#include<cstdio>
const int N = 1e2;
const int way[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int n,m,s,x,y,i,j,d;
bool c[N + 2][N + 2];
int main() {
	scanf("%d%d%d",&n,&m,&s);
	for(i=1; i<=s; ++i) {
		if(c[x][y])
			c[x][y]=false,
			        (d+=3)%=4;
		else
			c[x][y]=true,
			        (d+=1)%=4;
		x=(x+n+way[d][0])%n;
		y=(y+m+way[d][1])%m;
	}
	for(i=0; i<n; ++i) {
		for(j=0; j<m; ++j)
			putchar(c[i][j]?'#':'.');
		putchar('\n');
	}
	return 0;
}