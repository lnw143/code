#include<cstdio>
#include<stack>
using namespace std;
const int N = 300, M = 2e6;
int T,n,m,k,i,a[M + 2];
struct {
	int op,x,y;
} o[M * 2 + 2];
void opt(int op,int x,int y=0) {
	o[++tot].op=op;
	o[++tot].x=x;
	o[++tot].y=y;
}
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d%d",&n,&m,&k);
		
	}
	return 0;
}