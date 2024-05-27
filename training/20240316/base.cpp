#include<cstdio>
#include<cstring>
#include<map>
#include<bitset>
using namespace std;
const int N = 2e5, A = 4;
const map<char,int> mp={{'Z', 0}, {'P', 1}, {'S', 2}, {'B', 3}};
int n,m,k,s[N + 2][A + 2],ans;
char a[N + 2],b[N + 2];
bitset<N> bp[A + 2],pos,tmp;
inline int loc(int p) {
	return p>n?n:p<0?0:p;
}
int main() {
	freopen("base.in", "r", stdin);
	freopen("base.out", "w", stdout);
	scanf("%d%s%s",&k,a+1,b+1);
	n=strlen(a+1);
	m=strlen(b+1);
	for(int i=1; i<=m; ++i)
		bp[mp.at(b[i])].set(i-1);
	for(int i=1; i<=n; ++i) {
		for(int j=0; j<A; ++j)
			s[i][j]=s[i-1][j];
		++s[i][mp.at(a[i])];
	}
	pos.set(0);
	for(int i=1; i<=n; ++i) {
		tmp.reset();
		for(int j=0; j<A; ++j)
			if(s[loc(i-k-1)][j]<s[loc(i+k)][j])
				tmp|=bp[j];
		pos&=tmp;
		ans+=pos[m-1];
		pos<<=1;
		pos.set(0);
	}
	printf("%d",ans);
	return 0;
}