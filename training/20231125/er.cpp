#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N = 2 + 2, M = 100 + 2, S = M * 2e3 / 2 + 2;
int n,m,k,i,a[N],type,x,add[M],mul[M],an,mn,gv;
double g[M],sum[M],ans;
bool f[S];
double work(int a,int b,int k) {
	if(k==0) return log(a*b);
	if(~b) {
		double maxn=log(a*b)+sum[k];
		int s=a+b,ls=0;
		memset(f,0,sizeof(f));
		f[a]=true;
		for(int i=1; i<=an&&i<=k; ++i) {
			s+=add[i];
			for(int j=s; j>=add[i]&&j>=ls; --j)
				f[j]=f[j]||f[j-add[i]];
			for(int j=s/2; j>=ls; --j)
				if(f[j]) {
					ls=j;
					break;
				}
			maxn=max(maxn,log(ls)+log(s-ls)+sum[max(0,k-i)]);
		}
		return maxn;
	} else {
		double maxn=log(a)+sum[k];
		for(int i=1; i<=an&&i<=k; ++i)
			maxn=max(maxn,log(a+=add[i])+sum[max(0,k-i)]);
		return maxn;
	}
}
bool cmp(int x,int y) {
	return x>y;
}                    
int main() {
	scanf("%d%d%d",&n,&m,&k);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	if(n==1) a[2]=-1;
	gv=-1;
	for(i=1; i<=m; ++i) {
		scanf("%d",&type);
		if(type==1)
			scanf("%d",&gv);
		else if(type==2)
			scanf("%d",&add[++an]);
		else
			scanf("%d",&mul[++mn]);
	}
	stable_sort(add+1,add+an+1,cmp);
	stable_sort(mul+1,mul+mn+1,cmp);
	an=min(an,k);
	mn=min(mn,k);
	for(i=1; i<=mn; ++i)
		g[i]=log(mul[i]),sum[i]=sum[i-1]+g[i];
	for(i=mn; i<k; ++i)
		sum[i+1]=sum[i];
	ans=work(a[1],a[2],k);
	if(gv!=-1) {
		ans=max(ans,work(gv,a[2],k-1));
		if(n>1) ans=max(ans,work(a[1],gv,k-1));
	}
	printf("%.3lf",ans);
	return 0;
}
