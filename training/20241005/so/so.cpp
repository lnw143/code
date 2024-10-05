#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
using LL = __int128_t;
const int M = 14, S = M * M;
ll n;
LL ans;
int m,a[M + 2];
LL exgcd(LL a,LL b,LL &x,LL &y) {
	if(!b) {
		x=1,y=0;
		return a;
	}
	LL d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
struct ModEqua {
	LL a,m;
} e[S + 2];
int cnt;
ModEqua excrt(LL a,LL b,LL c,LL d) {
	LL x,y;
	LL g=exgcd(b,d,x,y);
	if((a-c)%g) return {-1,-1};
	LL m=b/g*d;
	LL res=((a-c)/g)*y%m*d%m+c;
	return {(res%m+m)%m,m};
}
ModEqua operator&(const ModEqua& x,const ModEqua& y) {
	if(x.a==-1||y.a==-1) return {-1,-1};
	return excrt(x.a,x.m,y.a,y.m);
}
bool operator==(const ModEqua& x,const ModEqua& y) {
	return x.a==y.a&&x.m==y.m;
}
ll calc(const ModEqua& x) {
	if(x.a>n) return 0;
	return (n-x.a)/x.m+1;
}
void dfs(int u,ModEqua x,int sum) {
	if(x.a==-1||x.a>n) return ;
	if(u>cnt) {
		if(sum) {
			if(sum&1) ans+=calc(x);
			else ans-=calc(x);
		}
		return ;
	}
	dfs(u+1,x,sum);
	dfs(u+1,x&e[u],sum+1);
}
int main() {
	freopen("so.in","r",stdin);
	freopen("so.out","w",stdout);
	scanf("%lld%d",&n,&m);
	if(m==0) return printf("0"),0;
	for(int i=1; i<=m; ++i) {
		scanf("%d",&a[i]);
		if(a[i]==1) return printf("%lld",n),0;
	}
	vector<ModEqua> tmp;
	for(int i=1; i<=m; ++i)
		for(int j=1; j<=m; ++j)
			if(i!=j) {
				ModEqua res=ModEqua{0,a[i]}&ModEqua{1,a[j]};
				if(res.a!=-1) tmp.push_back(res);
			}
	sort(tmp.begin(),tmp.end(),[](auto x,auto y) {
		return x.m<y.m;
	});
	for(int i=0; i<tmp.size(); ++i) {
		bool ok=true;
		for(int j=0; j<i; ++j)
			if((tmp[j]&tmp[i])==tmp[i]) {
				ok=false;
				break;
			}
		if(ok) e[++cnt]=tmp[i];
	}
	dfs(1,{0,1},0);
	bool no=true;
	for(int i=1; i<=m; ++i)
		if(n%a[i]==0) {
			no=false;
			break;
		}
	if(no) {
		for(int i=1; i<=m; ++i)
			if(n%a[i]==1) {
				++ans;
				break;
			}
	}
	printf("%lld",ll(ans));
	return 0;
}