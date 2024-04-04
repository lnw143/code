#include<cstdio>
using namespace std;
const int N = 1e6;
int n,rk[2][N + 2],sa[N + 2];
char s[N + 2];
void Sort() {

}
int main() {
	scanf("%d%s",&n,s+1);
	for(int i=1; i<=n; ++i)
		rk[0][i]=s[i];
	for(int j=0; (1<<j)<=n; ++j) {
		const int k=j&1,t=k^1,l=1<<j;
		for(int i=1; i+l-1<=n; ++i) {
			if()
		}
	}
	return 0;
}