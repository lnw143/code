#include<cstdio>
#include<algorithm>
#define pw2(x) (1ll<<(x))
using namespace std;
using ll = long long;
int T,i;
ll a,b,r,x,ans;
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%lld%lld%lld",&a,&b,&r);
		if(a<b) swap(a,b);
		ans=0;
		bool first=true;
		for(i=63; i>=0; --i) {
			if(!first&&(a&pw2(i))&&(b&pw2(i))==0&&(ans|pw2(i))<=r) {
				ans|=pw2(i);
				a^=pw2(i);
				b^=pw2(i);
				if(a<b) swap(a,b);
			}
			if((a&pw2(i))&&(b&pw2(i))==0) first=false;
		}
		printf("%lld\n",a-b);
	}
	return 0;
}