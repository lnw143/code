#include<cstdio>
using namespace std;
const int N = 9 + 2;
int n=9,m=3,i,j,x;
bool r[N][N],l[N][N],g[N][N];
int main() {
	for(i=1; i<=n; ++i)
		for(j=1; j<=n; ++j) {
			scanf("%d",&x);
			if(r[i][x]||l[j][x]||g[(j-1)/3*3+(i-1)/3][x]) {
				printf("No");
				return 0;
			} else
				r[i][x]=l[j][x]=g[(j-1)/3*3+(i-1)/3][x]=true;
		}
	printf("Yes");
	return 0;
}