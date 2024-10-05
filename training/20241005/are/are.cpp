#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
inline char gc() {
	static char buf[1<<20],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,1<<20,stdin),l==r)?-1:*l++;
}
inline int read() {
	int x=0;
	bool f=false;
	char c=gc();
	for(; c<'0'||c>'9'; c=gc()) if(c=='-') f=true;
	for(; c>='0'&&c<='9'; c=gc()) x=(x<<1)+(x<<3)+(c&15);
	return f?-x:x;
}
const int N = 5e5;
int n,k,p[N + 2],dep[N + 2],rem[N + 2],ans;
bool vis[N + 2];
vector<int> cir,e[N + 2];
void init() {
	int u=1;
	for(; !vis[u]; u=p[u]) vis[u]=true;
	cir.clear();
	cir.push_back(u);
	for(int v=p[u]; v!=u; v=p[v]) cir.push_back(v);
	static int q[N + 2];
	int h=1,t=0;
	for(auto i : cir) {
		dep[i]=1;
		q[++t]=i;
	}
	for(; h<=t; ++h)
		for(auto v : e[q[h]])
			if(!dep[v]) {
				dep[v]=dep[q[h]]+1;
				q[++t]=v;
			}
}
int calc2(vector<int> sta) {
	int res=0;
	for(int i=0; i<sta.size(); )
		if(sta[i])
			++res,i+=k;
		else
			++i;
	return res;
}
int calc(vector<int> sta) {
	if(sta.size()<=k) {
		for(auto i : sta)
			if(i)
				return 1;
		return 0;
	}
	vector<int> tmp=sta;
	sta.insert(sta.begin(),tmp.begin(),tmp.end());
	int res=tmp.size();
	{
		int last=-1,pos=0,maxn=0;
		for(int i=0; i<tmp.size(); ++i)
			if(sta[i])
				last=i;
			else if(i-last>maxn) {
				maxn=i-last;
				pos=last+1;
			}
		res=min(res,calc2(vector<int>(sta.begin()+pos,sta.begin()+pos+tmp.size())));
	}
	{
		int pos=0,maxn=count(sta.begin(),sta.begin()+k,1),cur=maxn;
		for(int i=k; i<sta.size(); ++i) {
			cur+=sta[i]-sta[i-k];
			if(cur>maxn) {
				maxn=cur;
				pos=i-k;
			}
		}
		res=min(res,calc2(vector<int>(sta.begin()+pos,sta.begin()+pos+tmp.size())));
	}
	return res;
}
void solve() {
	memset(dep,0,sizeof(dep));
	memset(rem,0,sizeof(rem));
	memset(vis,0,sizeof(vis));
	n=read(),k=read();
	for(int i=1; i<=n; ++i) {
		int u=read(),v=read();
		p[u]=v;
		e[v].push_back(u);
	}
	init();
	vector<int> vex;
	for(int i=1; i<=n; ++i) if(dep[i]>1) vex.push_back(i);
	sort(vex.begin(),vex.end(),[](int x,int y) { return dep[x]>dep[y]; });
	rem[1]=k+1;
	ans=0;
	for(auto u : vex) {
		for(auto v : e[u])
			rem[u]=max(rem[u],rem[v]-1);
		if(rem[u]==0) {
			rem[u]=k;
			++ans;
		}
	}
	for(auto u : cir)
		for(auto v : e[u])
			rem[u]=max(rem[u],rem[v]-1);
	for(auto u : cir)
		for(auto v : e[u])
			rem[u]=max(rem[u],rem[v]-1);
	vector<int> sta;
	for(auto u : cir)
		sta.push_back(!rem[u]);
	printf("%d\n",ans+calc(sta));
	for(int i=1; i<=n; ++i) e[i].clear();
}
int main() {
	freopen("are.in","r",stdin);
	freopen("are.out","w",stdout);
	read();
	for(int T=read(); T; --T)
		solve();
	return 0;
}