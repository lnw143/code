#include<cstdio>
using namespace std;
const int N = 1e5 + 2;
typedef long long ll;
int n,b[N],c[N],em,e[N],ls[N],nx[N],fa[N],u,v,l,r,md;
ll a[N];
void insert(int x,int y) {
	e[++em]=y;
	nx[em]=ls[x];
	ls[x]=em;
}
void dfs(int x) {
	for(int i=ls[x]; i; i=nx[i])
		if(e[i]!=fa[x]) {
			fa[e[i]]=x;
			dfs(e[i]);
		}
}
bool wk(int x,int t) {
	if(c[i]>=0) {
		int l=1,r=t,md=0;
		while(l<=r) {
			md=(l+r)/2;
			if(double(b[x]+md*c[x]+b[x]+r*c[x])*(t-md+1)/2>=a[x])
				l=md+1;
			else
				r=md-1;
		}
		if(r==0) return false;
		q[x]=l-1;
	} else {
		
	}
}
bool ck(int t) {
	for(int i=1; i<=n; ++i)
		if(!wk(i,t))	
			return false;
}
int main() {
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		scanf("%d%d%d",&a[i],&b[i],&c[i]);
	for(i=1; i<n; ++i) {
		scanf("%d%d",&u,&v);
		insert(u,v);
		insert(v,u);
	}
	dfs(1);
	l=1,r=1e9;
	while(l<=r) {
		md=(l+r)/2;
		if(ck(md))
			r=mid-1;
		else
			l=mid+1;
	}
	printf("%d",r+1);
	return 0;
}