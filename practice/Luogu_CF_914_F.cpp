#include<cstdio>
#include<cstring>
#include<bitset>
using namespace std;
const int N = 1e5 + 2, C = 26 + 2;
int n,q,op,i,j,l,r;
char s[N],y[N],c;
bitset<N> bs[C],ans;
int main() {
	scanf("%s%d",s+1,&q);
	for(i=1; s[i]; ++i)
		bs[s[i]-'a'][i]=true;
	for(i=1; i<=q; ++i) {
		scanf("%d",&op);
		if(op==1) {
			scanf("%d %c",&l,&c);
			bs[s[l]-'a'][l].flip();
			bs[c-'a'][l]=true;
			s[l]=c;
		} else {
			scanf("%d%d%s",&l,&r,y+1);
			n=strlen(y+1);
			if(r-l+1<n) {
				printf("0\n");
				continue;
			}
			ans.set();
			for(j=1; j<=n; ++j)
				ans&=bs[y[j]-'a']>>(j-1);
			printf("%d\n",(ans<<(N-r+n-2)>>(N-r+n-2+l)).count());
		}
	}
	return 0;
}