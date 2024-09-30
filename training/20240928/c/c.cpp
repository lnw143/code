#include <cstdio>
#include <cassert>
#include <set>
using namespace std;
using ll = long long;
const int N = 2e5;
int n,k,l[N + 2],r[N + 2];
namespace ODT {
	struct node {
		int l,r,c;
	};
	bool operator<(const node& x,const node& y) {
		return x.l<y.l;
	}
	set<node> odt;
	using iter=set<node>::iterator;
	bool operator<(const iter& x,const iter& y) {
		return x->l<y->l;
	}
	set<iter> p[N + 2];
	iter insert(node x) {
		iter it=odt.insert(x).first;
		if(x.c) p[x.c].insert(it);
		return it;
	}
	int cur,lst;
	ll sum;
	void init() {
		for(int i=1; i<=n; ++i) p[i].clear();
		sum=lst=cur=0;
		odt.clear();
		odt.insert({0,int(1e9),0});
	}
	iter split(int x) {
		iter it=odt.lower_bound({x,0,0});
		if(it!=odt.end()&&it->l==x) return it;
		assert(it!=odt.begin());
		auto [l,r,c]=*--it;
		if(c) p[c].erase(it);
		odt.erase(it);
		insert({l,x-1,c});
		return insert({x,r,c});
	}
	void add(int l,int r,int c) {
		iter itr=split(r+1),itl=split(l);
		for(auto i=itl; i!=itr; ++i) {
			if(i->c==0) continue;
			if(i->c>lst)
				cur-=i->r-i->l+1;
			else
				sum-=(i->r-i->l+1)*ll(i->c);
			p[i->c].erase(i);
		}
		cur+=r-l+1;
		odt.erase(itl,itr);
		insert({l,r,c});
	}
	void to_next() {
		++lst;
		for(auto it : p[lst])
			cur-=it->r-it->l+1,
			sum+=(it->r-it->l+1)*ll(lst);
	}
}
ll get_rank(int x) {
	ODT::init();
	ll res=0;
	for(int i=1; i<=n; ++i) {
		ODT::add(l[i],r[i],i);
		while(ODT::cur>=x) ODT::to_next();
		res+=ODT::lst;
	}
	return res;
}
ll get_ans(int lim) {
	ODT::init();
	ll res=0;
	for(int i=1; i<=n; ++i) {
		ODT::add(l[i],r[i],i);
		while(ODT::cur>=lim) ODT::to_next();
		res+=ll(ODT::lst)*ODT::cur+ODT::sum;
	}
	return res;
}
int main() {
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; ++i) scanf("%d%d",&l[i],&r[i]),--r[i];
	int l=1,r=1e9;
	while(l<=r) {
		int mid=(l+r)/2;
		if(get_rank(mid)<=k) r=mid-1;
		else l=mid+1;
	}
	// printf("%lld\n",get_rank(5));
	printf("%lld",get_ans(r+1));
	return 0;
}