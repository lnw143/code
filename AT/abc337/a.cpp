#include<cstdio>
using namespace std;
int n,a,b,f,g;
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		scanf("%d%d",&a,&b);
		f+=a,g+=b;
	}
	printf(f==g?"Draw":f<g?"Aoki":"Takahashi");
	return 0;
}