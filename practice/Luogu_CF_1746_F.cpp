#include<cstdio>
#include<random>
#include<unordered_map>
using namespace std;
const int N = 3e5, K = 100;
int n,q,a[N + 2],tot;
mt19937 rnd(random_device{}());
unordered_map<int,int> mp;
int id(int x) { return mp.count(x)?mp[x]:mp[x]=++tot; }
struct fenwick {
	bool bz[N + 2];
	int t[N + 2];
	void init() {
		for(int i=1; i<=n+q; ++i)
			bz[i]=rnd()&1;
	}
	void add(int i,int x,int type) {
		x=id(x);
		if(!bz[x]) return ;
		while(i<=n) {
			t[i]+=type;
			i+=i&-i;
		}
	}
	int sum(int i) {
		int r=0;
		while(i) {
			r+=t[i];
			i&=i-1;
		}
		return r;
	}
	int sum(int l,int r) {
		return sum(r)-sum(l-1);
	}
	bool check(int l,int r,int k) {
		return sum(l,r)%k==0;
	}
} f[K];
int main() {
	scanf("%d%d",&n,&q);
	for(int j=0; j<K; ++j)
		f[j].init();
	for(int i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
		for(int j=0; j<K; ++j)
			f[j].add(i,a[i],1);
	}
	for(int i=1; i<=q; ++i) {
		int op;
		scanf("%d",&op);
		if(op==1) {
			int p,x;
			scanf("%d%d",&p,&x);
			for(int j=0; j<K; ++j) {
				f[j].add(p,a[p],-1);
				f[j].add(p,x,1);
			}
			a[p]=x;
		} else {
			int l,r,k;
			scanf("%d%d%d",&l,&r,&k);
			if(k==1) {
				printf("YES\n");
				continue;
			}
			if((r-l+1)%k!=0) {
				printf("NO\n");
				continue;
			}
			bool ans=true;
			for(int j=0; j<K; ++j)
				if(!f[j].check(l,r,k)) {
					ans=false;
					break;
				}
			printf(ans?"YES\n":"NO\n");
		}
	}
	return 0;
}