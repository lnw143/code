#include<cstdio>
#include<cmath>
#include<algorithm>
#include<random>
using namespace std;
using ll = long long;
using db = long double;
mt19937 rnd(random_device{}());
const int N = 2e5;
const db RND_MAX = pow(2,32), Begin_ = 1e6, End_ = 1e-3, Next_ = 1-3e-5;
int T,n,i,em,e[N * 2],ls[N + 2],nx[N * 2],cs[N * 2];
ll ans;
void insert(int x,int y,int z) {
    e[++em]=y;
    nx[em]=ls[x];
    cs[em]=z;
    ls[x]=em;
}
db myrnd() {
    return rnd()/RND_MAX;
}
namespace CutTree {
    int top[N + 2],dfn[N + 2],rnk[N + 2],dep[N + 2],dfc,fa[N + 2],wson[N + 2],sz[N + 2],sum[N + 2];
    void dfs(int x) {
        sz[x]=1;
        wson[x]=0;
        for(int i=ls[x]; i; i=nx[i]) 
            if(e[i]!=fa[x]) {
                fa[e[i]]=x;
                dep[e[i]]=dep[x]+1;
                dfs(e[i]);
                sz[x]+=sz[e[i]];
                if(sz[e[i]]>sz[wson[x]])
                    wson[x]=e[i];
            }
    }
    void dfs2(int x,int tp) {
        top[x]=tp;
        dfn[x]=++dfc;
        rnk[dfc]=x;
        if(wson[x]) dfs2(wson[x],tp);
        for(int i=ls[x]; i; i=nx[i]) {
            if(e[i]!=wson[x]&&e[i]!=fa[x])
                dfs2(e[i],e[i]);
            if(e[i]!=fa[x])
                sum[dfn[e[i]]]=cs[i];
        }
    }
    void init_sum() {
        for(int i=2; i<=n; ++i)
            sum[i]+=sum[i-1];
    }
    int dis(int x,int y) {
        int ret=0;
        while(top[x]!=top[y]) {
            if(dep[top[x]]<dep[top[y]]) {
                ret+=sum[dfn[y]]-sum[dfn[top[y]]-1];
                y=fa[top[y]];
            } else {
                ret+=sum[dfn[x]]-sum[dfn[top[x]]-1];
                x=fa[top[x]];
            }
        }
        return ret+(dep[x]>dep[y]?sum[dfn[x]]-sum[dfn[y]]:sum[dfn[y]]-sum[dfn[x]]);
    }
}
struct X {
    int p[N + 2];
    ll ans;
    void init() {
        for(int i=1; i<=n; ++i)
            p[i]=i;
        shuffle(p+1,p+n+1,rnd);
        ans=0;
        for(int i=1; i<n; ++i)
            ans+=CutTree::dis(p[i],p[i+1]);
        ans+=CutTree::dis(p[1],p[n]);
    }
    int swp(int x) const {
        int a=p[x-1],b=p[x],c=p[x+1],d=p[x==n-1?1:x+2];
        using namespace CutTree;
        return ans+dis(a,c)-dis(a,b)+dis(b,d)-dis(c,d);
    }
};
void Random() {
    for(int ii=0; ii<2500; ++ii) {
        X y;
        y.init();
        ans=min(ans,y.ans);
    }
}
int main() {
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&n);
        em=0;
        for(i=1; i<=n; ++i) ls[i]=0;
        for(i=1; i<n; ++i) {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            insert(u,v,w);
            insert(v,u,w);
        }
        CutTree::dfs(1);
        CutTree::dfc=0;
        CutTree::dfs2(1,1);
        CutTree::init_sum();
        ans=1e18;
        Random();
        printf("%lld\n",ans);
    }
    return 0;
}