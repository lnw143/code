#include<cstdio>
#include<algorithm>
#define rep(i,l,r) for(int i(l),i##END(r); i<=i##END; ++i)
#define per(i,l,r) for(int i(r),i##END(l); i>=i##END; --i)
using namespace std;
const int N(1e3), inf(1<<30);
int T,n,q,a[N + 2],s[N + 2],f[N + 2][N + 2];
int check(int l,int r) {
    return (s[r]-s[l-1])*2>r-l+1;
}
int solve(int l,int r,int k) {
    rep(i,l,r)
        rep(j,0,k) 
            f[i][j]=-inf;
    f[l-1][0]=0;
    rep(i,l,r)
        rep(j,1,min(k,i-l+1)) {
            rep(h,l+j-1,i)
                f[i][j]=max(f[i][j],f[h-1][j-1]+check(h,i));
        }
    return f[r][k];
}
int main() {
    freopen("c.in","r",stdin);
    freopen("c.out","w",stdout);
    scanf("%d",&T);
    rep(id,1,T) {
        scanf("%d%d",&n,&q);
        rep(i,1,n)
            scanf("%1d",&a[i]),s[i]=s[i-1]+a[i];
        rep(i,1,q) {
            int l,r,k;
            scanf("%d%d%d",&l,&r,&k);
            printf("%d\n",solve(l,r,k));
        }
    }
    return 0;
}