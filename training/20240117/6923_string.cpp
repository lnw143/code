#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 1 << 20, A = 26;
using ui = unsigned int;
using ll = long long;
int T,z[N + 2],n,i,t[A + 2],f,g,es;
ll ans;
char s[N + 2];
#define pw2(x) (1<<(x))
struct Cnt {
	int sta,cnt;
	int ads(char c) {
		return cnt+=(sta^=pw2(c-'a'))&pw2(c-'a')?1:-1;
	}
	void reset() {
		sta=cnt=0;
	}
} u,v;
int main() {
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	scanf("%d",&T);
	while(T--) {
		scanf("%s",s+1);
		n=strlen(s+1);
		z[1]=0;
		u.reset();
		u.ads(s[1]);
		for(int i=2,l=1,r=0; i<=n; ++i) {
			u.ads(s[i]);
			if(i<=r&&z[i-l+1]<r-i+1)
				z[i]=z[i-l+1];
			else {
				z[i]=max(0,r-i+1);
				while(i+z[i]<=n&&s[z[i]+1]==s[i+z[i]])
					++z[i];
			}
			if(i+z[i]-1>r) l=i,r=i+z[i]-1;
		}
		f=u.cnt;
		ans=g=es=0;
		u.ads(s[1]);
		v.reset();
		memset(t,0,sizeof(t));
		for(i=2; i<n; ++i) {
			int p=v.ads(s[i-1]);
			++t[p];
			if(p<=f) ++g;
			if(p<=u.cnt) ++es;
			if(u.sta&pw2(s[i]-'a'))
				es-=t[u.cnt];
			else
				es+=t[u.cnt+1];
			u.ads(s[i]);
			int num=min(z[i+1],n-i-1)/i+1,even=num/2,odd=num-even;
			ans+=(ll)even*g+(ll)odd*es;
		}
		printf("%lld\n",ans);
	}
	return 0;
}