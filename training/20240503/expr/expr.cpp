#include<cstdio>
#include<cctype>
using namespace std;
using ll = long long;
constexpr int N = 1e6, P = 998244353;
int n,m,q,fa[N + 2],z[N + 2],sum;
ll a[N + 2],v[N + 2],ans;
char s[N + 2],p[N + 2];
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
void set(int x,int type) {
	if(p[x]=='/') {
		if(a[x]==0) sum+=type;
		else (v[fa[x]]*=(~type?qpow(a[x],P-2):a[x]))%=P;
	} else {
		if(a[x]==0) z[fa[x]]+=type;
		else (v[fa[x]]*=(~type?a[x]:qpow(a[x],P-2)))%=P;
	}
}
void add(int x,int type) {
	x=fa[x];
	if(z[x]) return ;
	if(p[x]=='-') type=-type;
	(ans+=type*v[x]+P)%=P;
}
void modify(int x,int &y) {
	add(fa[x],-1);
	set(x,-1);
	a[x]^=y^=a[x]^=y;
	set(x,1);
	add(fa[x],1);
}
int main() {
	freopen("expr.in","r",stdin);
	freopen("expr.out","w",stdout);
	scanf("%d%d%s",&n,&q,s+1);
	while(s[m+1]) ++m;
	for(int i=1,j=1; i<=m; ++i)
		if(!isdigit(s[i]))
			p[++j]=s[i];
		else
			a[j]=a[j]*10+s[i]-'0';
	fa[1]=1;
	v[1]=1;
	for(int i=2; i<=n; ++i)
		if(p[i]=='*'||p[i]=='/')
			fa[i]=fa[i-1];
		else
			fa[i]=i,v[i]=1;
	for(int i=1; i<=n; ++i)
		set(i,1);
	for(int i=1; i<=n; ++i)
		if(fa[i]==i)
			add(i,1);
	for(int i=1; i<=q; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		modify(x,y);
		if(sum) printf("Invalid\n");
		else printf("%lld\n",ans);
		modify(x,y);
	}
	return 0;
}