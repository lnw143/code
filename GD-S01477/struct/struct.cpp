#include<cstdio>
using namespace std;
const int N = 1e2 + 2, S = 10 + 2, Base = 131, M = 10007;
const char based_type[4][6] = {"byte","short","int","long"};
typedef long long ll;
typedef long long unsigned llu;
int n,i,j,h,op,m,type[N],p[N],q[N],now,k[M],t[M][N],a[M];
ll ans,addr,b[N],sz[M],o[M][N];
char s[S],vn[N][S],name[M][N][S];
llu id[M];
bool hs[M];
template<typename T>T max(T a,T b) {
	return a<b?b:a;
}
llu get_id(const char s[]) {
	llu ret=0;
	for(int i=0; s[i]; ++i)
		ret=ret*Base+s[i];
	return ret;
}
int hash(llu x) {
	int y=x%M;
	while(hs[y]&&id[y]!=x) ++y%=M;
	hs[y]=true;
	id[y]=x;
	return y;
}
ll div(ll a,ll b) {
	return (a+b-1)/b*b;
}
void read(int v) {
	a[v]=0;
	for(int i=1; i<=k[v]; ++i) {
		scanf("%s%s",s,name[v][i]);
		t[v][i]=hash(get_id(s));
		a[v]=max(a[v],a[t[v][i]]);
	}
	o[v][1]=0;
	for(int i=2; i<=k[v]; ++i)
		o[v][i]=div(o[v][i-1]+sz[t[v][i-1]],a[t[v][i]]);
	sz[v]=div(o[v][k[v]]+sz[t[v][k[v]]],a[v]);
}
bool read_str() {
	char ch=getchar();
	while(ch<'a'||ch>'z') ch=getchar();
	int len=0;
	while(ch>='a'&&ch<='z') {
		s[len]=ch;
		ch=getchar();
		++len;
	}
	s[len]=0;
	return ch=='.';
}
bool Strcmp(char *a,char *b) {
	while(*a&&*a==*b) ++a,++b;
	return *a==*b;
}
int main() {
	freopen("struct.in","r",stdin);
	freopen("struct.out","w",stdout);
	scanf("%d",&n);
	for(i=0; i<4; ++i) {
		int h=hash(get_id(based_type[i]));
		a[h]=sz[h]=1<<i;
	}
	for(i=1; i<=n; ++i) {
		scanf("%d",&op);
		switch(op) {
			case 1: {
				scanf("%s",s);
				h=hash(get_id(s));
				scanf("%d",&k[h]);
				read(h);
				printf("%lld %d",sz[h],a[h]);
				break;
			}
			case 2: {
				++m;
				scanf("%s%s",s,vn[m]);
				type[m]=hash(get_id(s));
				if(m==1) b[m]=0;
				else
					b[m]=div(b[m-1]+sz[type[m-1]],a[type[m]]);
				printf("%lld",b[m]);
				break;
			}
			case 3: {
				bool f=read_str();
				for(j=1; j<=m; ++j)
					if(Strcmp(s,vn[j])) {
						now=type[j];
						ans=b[j];
						break;
					}
				while(f) {
					f=read_str();
					for(j=1; j<=k[now]; ++j)
						if(Strcmp(s,name[now][j])) {
							ans+=o[now][j];
							now=t[now][j];
							break;
						}
				}
				printf("%lld",ans);
				break;
			}
			case 4: {
				scanf("%lld",&addr);
				for(j=1; j<=m; ++j)
					if(b[j]>addr)
						break;
				now=type[j-1];
				p[p[0]=1]=j-1;
				addr-=b[j-1];
				while(k[now]) {
					for(j=1; j<=k[now]; ++j)
						if(o[now][j]>addr)
							break;
					q[++p[0]]=now;
					addr-=o[now][j-1];
					now=t[now][j-1];
					p[p[0]]=j-1;
				}
				if(addr<sz[now]) {
					printf("%s",vn[p[1]]);
					for(j=2; j<=p[0]; ++j)
						printf(".%s",name[q[j]][p[j]]);
				} else
					printf("ERR");
				break;
			}
		}
		putchar('\n');
	}
	return 0;
}
