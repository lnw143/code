#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
using namespace std;
const int N = 9, M = 100, Bell9 = 21147;
int n,m;
int u[M + 2],v[M + 2],w[M * 2 + 2],id[M * 2 + 2];
int a[M * 2 + 2];
int f[2][M + 2][Bell9 + 2];
void chmax(int &x,int y) {
	if(y>x) x=y;
}
namespace automaton {
	int tot,son[Bell9 + 2][N + 2][N + 2];
	vector<int> sta[Bell9 + 2],ck[Bell9 + 2];
	map<long long,int> mp;
	int find(const vector<int>& fa,int u) { return fa[u]==u?u:find(fa,fa[u]); }
	int get_id(const vector<int>& fa) {
		vector<int> c(n,0),d(n);
		int k=0;
		long long h=0;
		for(int i=0; i<n; ++i) {
			int g=find(fa,i);
			if(!c[g]) c[g]=++k;
			h=h*10+c[g];
			d[i]=c[g];
		}
		if(!mp.count(h)) {
			mp[h]=++tot;
			sta[tot]=fa;
			ck[tot]=d;
		}
		return mp[h];
	}
	int get_final() {
		return get_id(vector<int>(n,0));
	}
	void expand(int u) {
		for(int i=0; i<n; ++i)
			for(int j=i+1; j<n; ++j) {
				vector<int> s=sta[u];
				int x=find(s,i),y=find(s,j);
				if(x==y) {
					son[u][i][j]=son[u][j][i]=u;
					continue;
				}
				s[x]=y;
				son[u][i][j]=son[u][j][i]=get_id(s);
			}
	}
	bool check(int u,int x,int y) {
		return ck[u][x]==ck[u][y];
	}
	void init() {
		vector<int> s(n,0);
		for(int i=0; i<n; ++i) s[i]=i;
		get_id(s);
		for(int i=1; i<=tot; ++i)
			expand(i);
	}
}
int main() {
	freopen("mst.in","r",stdin);
	freopen("mst.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=0; i<m; ++i) {
		scanf("%d%d%d%d",&u[i],&v[i],&w[i<<1],&w[i<<1|1]);
		--u[i],--v[i];
	}
	for(int i=1; i<=2*m; ++i) a[i]=i-1;
	sort(a+1,a+2*m+1,[](int x,int y) { return w[x]<w[y]; });
	for(int i=1; i<=2*m; ++i) id[a[i]]=i;
	automaton::init();
	using automaton::son;
	using automaton::check;
	using automaton::tot;
	memset(f[0],0xc0,sizeof(f[0]));
	f[0][0][1]=0;
	for(int i=1; i<=2*m; ++i) {
		memset(f[i&1],0xc0,sizeof(f[i&1]));
		auto now=f[i&1],past=f[i&1^1];
		for(int j=0; j<=m&&j<=i; ++j)
			for(int k=1; k<=tot; ++k) {
				if(past[j][k]<0) continue;
				if(id[a[i]^1]>i) {
					if(!check(k,u[a[i]>>1],v[a[i]>>1]))
						chmax(now[j+!(a[i]&1)][son[k][u[a[i]>>1]][v[a[i]>>1]]],past[j][k]+w[a[i]]);
					else
						chmax(now[j+!(a[i]&1)][k],past[j][k]);
					chmax(now[j+(a[i]&1)][k],past[j][k]);
				} else {
					if(!check(k,u[a[i]>>1],v[a[i]>>1]))
						chmax(now[j][son[k][u[a[i]>>1]][v[a[i]>>1]]],past[j][k]+w[a[i]]);
					else 
						chmax(now[j][k],past[j][k]);
				}
			}
	}
	int final=automaton::get_final();
	for(int i=0; i<=m; ++i) printf("%d\n",f[0][i][final]);
	return 0;
}