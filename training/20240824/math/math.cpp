#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
inline char gc() {
	static char *l,*r,buf[1<<16];
	return l==r&&(r=(l=buf)+fread(buf,1,1<<16,stdin),l==r)?-1:*l++;
}
inline int read() {
	int x=0;
	char c=gc();
	for(; c<'0'||c>'9'; c=gc());
	for(; c>='0'&&c<='9'; c=gc()) x=(x<<3)+(x<<1)+(c&15);
	return x;
}
char pbuf[1<<16],*pp=pbuf;
inline void pc(char c) {
	*pp++=c;
	if(pp-pbuf==1<<16) fwrite(pbuf,1,1<<16,stdout),pp=pbuf;
}
inline void write(long long x) {
	static char stk[1<<7];
	char *tp=stk;
	do *tp++=x%10; while(x/=10);
	while(tp!=stk) pc((*--tp)|48);
}
using namespace std;
const int N = 2e5, B = 450;
int n,q,num[N + 2],cnt;
vector<int> s[N + 2];
int tot,sum[B + 2][N + 2],sum2[B + 2][N + 2],id[N + 2],pos[B + 2];
long long ans[B + 2][B + 2];
int main() {
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
	n=read();
	for(int i=1; i<=n; ++i) {
		s[i].resize(read());
		for(auto &j : s[i])
			num[++cnt]=j=read();
		sort(s[i].begin(),s[i].end());
	}
	sort(num+1,num+cnt+1);
	cnt=unique(num+1,num+cnt+1)-num-1;
	for(int i=1; i<=n; ++i)
		for(auto &j : s[i])
			j=lower_bound(num+1,num+cnt+1,j)-num;
	for(int i=1; i<=n; ++i) {
		if(s[i].size()<B) continue;
		id[i]=++tot;
		pos[tot]=i;
		for(auto j : s[i])
			++sum[tot][j],
			++sum2[tot][j];
		for(int i=1; i<=cnt; ++i) sum[tot][i]+=sum[tot][i-1];
		for(int i=cnt; i>=1; --i) sum2[tot][i]+=sum2[tot][i+1];
	}
	for(int i=1; i<=tot; ++i)
		for(int j=1; j<=tot; ++j)
			for(auto k : s[pos[j]])
				ans[i][j]+=sum[i][k];
	q=read();
	for(int i=1; i<=q; ++i) {
		static int x,y;
		x=read();
		y=read();
		if(id[x]&&id[y]) write(ans[id[x]][id[y]]),pc('\n');
		else if(id[x]) {
			long long res=0;
			for(auto j : s[y])
				res+=sum[id[x]][j];
			write(res),pc('\n');
		} else if(id[y]) {
			long long res=0;
			for(auto j : s[x])
				res+=sum2[id[y]][j];
			write(res),pc('\n');
		} else {
			int j=0,res=0;
			for(auto k : s[y]) {
				while(j<s[x].size()&&s[x][j]<=k) ++j;
				res+=j;
			}
			write(res);
			pc('\n');
		}
	}
	fwrite(pbuf,1,pp-pbuf,stdout);
	return 0;
}