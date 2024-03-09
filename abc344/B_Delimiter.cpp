#include<cstdio>
using namespace std;
void dfs() {
	int x;
	if(scanf("%d",&x)==1) dfs(),
	printf("%d\n",x);
}
int main() {
	dfs();
	return 0;
}