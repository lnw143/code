#include<cstdio>
#include<cstring>
using namespace std;
const int N = 1e5, A = 26;
using ll = long long;
int n,i;
char ch;
namespace sam {
	const int S = N * 2 + 2;
	int las=1,tot=1,tr[S][A + 2],fa[S],len[S];
	void insert(int c) {
		int p=las,np=++tot;
		len[np]=len[p]+1;
		las=np;
		for(; p&&!tr[p][c]; p=fa[p]) tr[p][c]=np;
		if(!p) fa[np]=1;
		else {
			int q=tr[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else {
				int nq=++tot;
				memcpy(tr[nq],tr[q],sizeof(tr[nq]));
				fa[nq]=fa[q];
				fa[np]=fa[q]=nq;
				len[nq]=len[p]+1;
				for(; p&&tr[p][c]==q; p=fa[p])
					tr[p][c]=nq;
			}
		}
	}
	ll get_diff() {
		ll r=0;
		for(int i=2; i<=tot; ++i)
			r+=len[i]-len[fa[i]];
		return r;
	}
}
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i) {
		scanf(" %c",&ch);
		sam::insert(ch-'a');
	}
	printf("%lld",sam::get_diff());
	return 0;
}