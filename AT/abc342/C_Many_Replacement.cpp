#include<cstdio>
#include<set>
using namespace std;
using si = set<int>;
const int N(2e6), A(26);
int n,q,r[A + 2];
char s[N + 2],c,d;
si p[A + 2];
int main() {
	scanf("%d%s%d",&n,s+1,&q);
	for(int i=0; i<A; ++i)
		p[i].insert(i);
	for(int i=1; i<=q; ++i) {
		scanf(" %c %c",&c,&d);
		if(c!=d) {
			c-='a',d-='a';
			p[d].insert(p[c].begin(),p[c].end());
			p[c].clear();
		}
	}
	for(int i=0; i<A; ++i)
		for(int j:p[i])
			r[j]=i;
	for(int i=1; i<=n; ++i)
		putchar(r[s[i]-'a']+'a');
	return 0;
}