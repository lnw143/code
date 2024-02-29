#include<cstdio>
#include<cstring>
#include<queue>
#include<utility>
using namespace std;
using ll = long long;
const int N = 1e6, A = 26;
int i;
ll ans;
char s[N + 2];
namespace SAM {
	const int S = N * 2 + 2;
	int tot=1,las=1,fa[S],tr[S][A + 2],len[S],f[S];
	void copy(int x,int y) {
		fa[x]=fa[y];
		memcpy(tr[x],tr[y],sizeof(tr[x]));
	}
	void insert(int c) {
		int p=las,np=++tot;
		las=np;
		f[np]=1;
		len[np]=len[p]+1;
		for(; p&&!tr[p][c]; p=fa[p]) tr[p][c]=np;
		if(!p) fa[np]=1;
		else {
			int q=tr[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else {
				int nq=++tot;
				copy(nq,q);
				len[nq]=len[p]+1;
				fa[np]=fa[q]=nq;
				for(; p&&tr[p][c]==q; p=fa[p]) tr[p][c]=nq;
			}
		}
	}
	void dp() {
		static int deg[S];
		queue<int> q;
		for(int i=2; i<=tot; ++i)
			++deg[fa[i]];
		for(int i=1; i<=tot; ++i)
			if(deg[i]==0)
				q.push(i);
		while(!q.empty()) {
			int u=q.front();
			q.pop();
			f[fa[u]]+=f[u];
			if(--deg[fa[u]]==0)
				q.push(fa[u]);
			if(f[u]>1)
				ans=max(ans,(ll)f[u]*len[u]);
		}
	}
}
int main() {
	scanf("%s",s);
	for(i=0; s[i]; ++i)
		SAM::insert(s[i]-'a');
	SAM::dp();
	printf("%lld",ans);
	return 0;
}