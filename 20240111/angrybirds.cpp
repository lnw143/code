#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 18, M = 1 << N, inf = 0x7f7f7f7f;
using db = double;
using ui = unsigned int;
int T,n,m,i,j,bits[M + 2],f[M + 2],cnt,tot,ans;
db x[N + 2],y[N + 2];
ui op[M + 2],opr[M + 2];
bool is_zero(db x) {
	return abs(x)<1e-6;
}
bool same(db x,db y) {
	return is_zero(x-y);
}
void jg(db x1,db y1,db x2,db y2) {
	if(same(x1,x2)) {
		if(!same(y1,y2)) return ;
		ui ret=0;
		for(int i=1; i<=n; ++i)
			ret|=(ui)(same(x[i],x1)&&same(y[i],y1))<<(i-1);
		opr[++tot]=ret;
		return ;
	}
	db a=(y1/x1-y2/x2)/(x1-x2),b=y1/x1-a*x1;
	if(a>0||is_zero(a)||!same(b,y2/x2-a*x2)) return ;
	ui ret=0;
	for(int i=1; i<=n; ++i)
		ret|=(ui)same(a*x[i]*x[i]+b*x[i],y[i])<<(i-1);
	opr[++tot]=ret;
	return ;
}
int main() {
	freopen("angrybirds.in","r",stdin);
	freopen("angrybirds.out","w",stdout);
	for(i=1; i<M; ++i)
		bits[i]=bits[i&(i-1)]+1;
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		m=1<<n;
		tot=cnt=0;
		memset(f,0x7f,sizeof(f));
		ans=inf;
		f[0]=0;
		for(i=1; i<=n; ++i)
			scanf("%lf%lf",&x[i],&y[i]);
		for(i=1; i<n; ++i)
			for(j=i+1; j<=n; ++j)
				jg(x[i],y[i],x[j],y[j]);
		stable_sort(op+1,op+tot+1);
		for(i=1; i<=tot; ++i) {
			for(j=i+1; j<=tot; ++j)
				if((opr[j]|opr[i])==opr[j])
					break;
			if(j>tot)
				op[++cnt]=opr[i];
		}
		for(i=0; i<m; ++i)
			if(f[i]!=inf) {
				for(j=1; j<=cnt; ++j)
					f[i|op[j]]=min(f[i|op[j]],f[i]+1);
				ans=min(ans,f[i]+n-bits[i]);
			}
		printf("%d\n",ans);
	}
	return 0;
}