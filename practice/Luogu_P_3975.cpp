#include<cstdio>
#include<queue>
#include<utility>
#include<cstring>
using namespace std;
const int N = 5e5, A = 26;
int t,i,k;
char s[N + 2],ans[N + 2];
namespace SAM {
	const int S = N * 2 + 2;
	int tot=1,las=1,tr[S][A + 2],fa[S],len[S],sz[S],f[S];
	bool vis[S];
	void insert(int c) {
		int p=las,np=++tot;
		len[np]=len[p]+1;
		sz[np]=1;
		las=np;
		for(; p&&!tr[p][c]; p=fa[p]) tr[p][c]=np;
		if(!p) fa[np]=1;
		else {
			int q=tr[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else {
				int nq=++tot;
				len[nq]=len[p]+1;
				fa[nq]=fa[q];
				fa[np]=fa[q]=nq;
				memcpy(tr[nq],tr[q],sizeof(tr[nq]));
				for(; p&&tr[p][c]==q; p=fa[p])
					tr[p][c]=nq;
			}
		}
	}
	int get_sz(int x) {
		if(vis[x]) return sz[x];
		vis[x]=true;
		for(int i=0; i<A; ++i)
			if(tr[x][i])
				sz[x]+=get_sz(tr[x][i]);
		return sz[x];
	}
	void sol_sz(int t) {
		if(t) {
			get_sz(1);
			for(int i=1; i<=tot; ++i)
				vis[i]=false;
		} else
			for(int i=1; i<=tot; ++i)
				sz[i]=1;
	}
	int dfs(int x) {
		if(vis[x]) return f[x];
		vis[x]=true;
		f[x]=sz[x];
		printf("%d %d\n",x,len[x]-len[fa[x]]);
		for(int i=0; i<A; ++i)
			if(tr[x][i])
				f[x]+=dfs(tr[x][i]);
		return f[x];
	}
	int get_ans(char *s,int k) {
		if(k>f[1]) return -1;
		int u=1;
		while(k>0) {
			for(int i=0; i<A; ++i) {
				if(!tr[u][i]) continue;
				if(k<=f[tr[u][i]]) {
					*s=i+'a';
					u=tr[u][i];
					--k;
					break;
				} else
					k-=f[tr[u][i]];
			}
			++s;
		}
		return k>0?-1:0;
	}
	void print() {
		for(int i=1; i<=tot; ++i)
			for(int j=0; j<A; ++j)
				if(tr[i][j])
					printf("%d(%d) %d(%d) %c\n",i,f[i],tr[i][j],f[tr[i][j]],j+'a');
	}
}
int main() {
	scanf("%s",s);
	for(i=0; s[i]; ++i)
		SAM::insert(s[i]-'a');
	scanf("%d%d",&t,&k);
	SAM::sol_sz(t);
	SAM::dfs(1);
	SAM::print();
	if(~SAM::get_ans(ans,k))
		printf("%s",ans);
	else
		printf("-1");
	return 0;
}