#include<cstdio>
using namespace std;
const int N = 1e4 + 2;
using ll = long long;
int n,v[N],a[N],i,j,k,l,sl[N],sr[N],ql[N],qr[N],tot;
ll sum,sum2,f[N],ans;
bool flag;
template<typename T>T min(T a,T b) {
	return a<b?a:b;
}
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		scanf("%d",&v[i]);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	for(i=1,j=n,flag=true; i<j&&flag;)
		for(k=i,l=j+1,sum=sum2=0,flag=false; k<=j; ++k) {
			sum+=v[k];
			while(sum2<sum&&k<l)
				sum2+=v[--l];
			if(k>=l) break;
			if(sum==sum2) {
				flag=true;
				++tot;
				sl[tot]=k-i+1;
				sr[tot]=j-l+1;
				ql[tot]=sl[tot]+ql[tot-1];
				qr[tot]=sr[tot]+qr[tot-1];
				i=k+1,j=l-1;
				break;
			}
		}
	ans=a[n];
	for(i=1; i<=tot; ++i) {
		f[i]=a[n];
		for(j=0; j<i; ++j)
			f[i]=min(f[i],f[j]+a[ql[i]-ql[j]]+a[qr[i]-qr[j]]);
		ans=min(ans,f[i]+a[n-ql[i]-qr[i]]);
	}
	printf("%lld",ans);
	return 0;
}