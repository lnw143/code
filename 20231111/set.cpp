#include<cstdio>
using namespace std;
const int prime[] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}, N = 1e2 + 2;
int a,b,p,i,j,fa[N];
int ans;
int gcd(int x,int y) {
	for(int i=25; i>=1; --i)
		if(x%prime[i]==0&&y%prime[i]==0)
			return prime[i];
	return 0;
}
int fd(int x) {
	return fa[x]==x?x:fa[x]=fd(fa[x]);
}
int main() {
	scanf("%d%d%d",&a,&b,&p);
	for(i=a; i<=b; ++i)
		fa[i]=i;
	for(i=a; i<=b; ++i)
		for(j=a; j<i; ++j)
			if(gcd(i,j)>=p)
				fa[fd(i)]=fd(j);
	for(i=a; i<=b; ++i)
		if(fa[i]==i)
			++ans;
	printf("%d",ans);
	return 0;
}