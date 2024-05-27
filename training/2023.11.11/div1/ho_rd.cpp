#include<cstdio>
#include<random>
using namespace std;
random_device rd;
mt19937 rnd(rd());
int n,m,i,j,ans;
int fc(int x) {
	int ret=0;
	while(x) {
		ret+=x%10;
		x/=10;
	}
	return ret;
}
int main() {
	freopen("holiday.in","w",stdout);
	n=rnd()%10000+1;
	m=rnd()%10000+1;
	printf("%d %d",n,m);
	fclose(stdout);
	for(i=1; i<=n; ++i)
		for(j=1; j<=m; ++j)
			if(fc(i)==fc(j))
				++ans;
	freopen("holiday.ans","w",stdout);
	printf("%d",ans);
	return 0;
}