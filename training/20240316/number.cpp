#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
using namespace std;
using ll = long long;
const int
	N = 1e2,
	T = 5,
	M = 11,
	A = 10,
	inf = 1 << 30
;
int n,pre[A + 2];
char s[T + 2];
namespace acam {
	const int S = N * T;
	int tot,tr[S + 2][A + 2],fail[S + 2],g[S + 2];
	ll f[M + 2][S + 2];
	void insert(const char *s) {
		int u=0,n=strlen(s);
		for(int i=0; i<n; ++i) {
			if(!tr[u][s[i]-'0']) g[tr[u][s[i]-'0']=++tot]=inf;
			u=tr[u][s[i]-'0'];
		}
		g[u]=n;
	}
	void build() {
		queue<int> q;
		for(int i=0; i<A; ++i)
			if(tr[0][i])
				q.push(tr[0][i]);
		g[0]=inf;
		while(!q.empty()) {
			int u=q.front();
			q.pop();
			g[u]=min(g[u],g[fail[u]]);
			for(int i=0; i<A; ++i)
				if(tr[u][i])	
					fail[tr[u][i]]=tr[fail[u]][i],q.push(tr[u][i]);
				else
					tr[u][i]=tr[fail[u]][i];
		}
	}
	ll dp() {
		f[1][tr[0][1]]=g[tr[0][1]]>pre[1];
		for(int i=2; i<=M; ++i)
			for(int u=0; u<=tot; ++u)
				for(int j=0; j<A; ++j)
					if(g[tr[u][j]]>pre[i])
						f[i][tr[u][j]]+=f[i-1][u];
		ll ans=0;
		for(int i=0; i<=tot; ++i)
			ans+=f[M][i];
		return ans;
	}
}
const vector<string> format = {"xxx-xxx-xxxxx", "xxx-xxxx-xxxx", "xxxx-xxxx-xxx", "xxxx-xxx-xxxx"};
vector<vector<int>> form;
int main() {
	// init format
	for(auto &s : format) {
		form.push_back(vector<int>());
		auto &a=form.back();
		a.push_back(0);
		for(int i=0,j=0; i<s.size(); ++i)
			if(s[i]=='x') {
				a.push_back(++j);
				if(i+1<s.size()&&s[i+1]=='-') j=0;
			}
	}
	for(auto &a : form)
		for(int i=1; i<=M; ++i)
			pre[i]=max(pre[i],a[i]);
	// input
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		scanf("%s",s);
		acam::insert(s);
	}
	// dp on acam
	acam::build();
	printf("%lld",acam::dp());
	return 0;
}