#include<cstdio>
#include<random>
using namespace std;
mt19937 rnd(random_device{}());
uniform_int_distribution<int> d(-1e3,1e3);
int T=1,n=13,i;
int main() {
    freopen("tree.in","w",stdout);
    printf("%d\n",T);
    while(T--) {
        printf("%d\n",n);
        for(i=2; i<=n; ++i)
            printf("%d %d %d\n",i,rnd()%(i-1)+1,d(rnd));
    }
    return 0;
}