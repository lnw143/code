#include<cstdio>
using namespace std;
const int N(5e5);
int n,m;
char s[N + 2];
namespace SAM {
	const int S(N * 2 + 2), A(26);
	int ch[S][A],len[S],fa[S],las,tot;
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
	
}
int main() {
	return 0;
}