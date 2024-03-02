#include<cstdio>
#include<vector>
using namespace std;
const int N(5e5), LOG_N(19 + 2);
int n,m;
char s[N + 2];
namespace SAM {
	const int S(N * 2 + 2), A(26);
	int ch[S][A],len[S],fa[S],las=1,tot=1;
	void insert(int c) {
		int p=las,np=++tot;
		las=np;
		len[np]=len[p]+1;
		for(; p&&!ch[p][c]; p=fa[p]) ch[p][c]=np;
		if(!p) fa[np]=1;
		else {
			int q=ch[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else {
				int nq=++tot;
				fa[nq]=fa[q];
				strcpy(ch[nq],ch[q]);
				len[nq]=len[p]+1;
				fa[q]=fa[np]=nq;
				for(; p&&ch[p][c]==q; p=fa[p]) ch[p][c]=nq;
			}
		}
	}
	namespace tree {
		int anc[N + 2][LOG_N];
		vector<int> e[N + 2];
		void dfs(int u) {
			for(int i=1; i<LOG_N; ++i)
				anc[u][i]=anc[anc[u][i-1]][i-1];
			for(int v:e[u])
				dfs(v);
		}
		void maketree() {
			for(int i=2; i<=tot; ++i)
				anc[i][0]=fa[i],
				e[fa[i]].push_back(i);
			anc[1][0]=1;
			dfs(1);
		}
		vector<int> ve[N + 2];
		
	}
}
int main() {
	scanf("%d%d%s",&n,&m,s+1);
	for(int i=n; i>=1; --i)
		SAM::insert(s[i]-'a');
	
	
	return 0;
}