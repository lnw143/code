#include <cstdio>
#include <vector>
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
	int len[N + 2],tp[N + 2],tot,cur,lst;
	ll sum;
	struct option {
		int pos,val;
	};
	vector<option> op;
	using iter = set<node>::iterator;
	iter insert(node x) {
		iter it=odt.insert(x).first;
		if(x.c) op.push_back({x.c,x.r-x.l+1});
		return it;
	}
	void clear() {
		for(int i=1; i<=n; ++i) len[i]=0;
		sum=lst=tot=cur=0;
	}
	iter split(int x) {
		iter it=odt.lower_bound({x,0,0});
		if(it!=odt.end()&&it->l==x) return it;
		auto [l,r,c]=*--it;
		if(c) op.push_back({c,-(r-l+1)});
		odt.erase(it);
		insert({l,x-1,c});
		return insert({x,r,c});
	}
	void add(int l,int r,int c) {
		iter itr=split(r+1),itl=split(l);
		for(auto i=itl; i!=itr; ++i) {
			if(i->c==0) continue;
			op.push_back({i->c,-(i->r-i->l+1)});
		}
		tot+=r-l+1;
		odt.erase(itl,itr);
		insert({l,r,c});
	}
	void ins(int k) {
		for(; cur<tp[k]; ++cur) {
			auto [i,j]=op[cur];
			len[i]+=j;
			if(i<=lst) sum+=j*ll(i);
			else tot+=ll(j);
		}
	}
	void to_next() {
		++lst;
		tot-=len[lst];
		sum+=len[lst]*ll(lst);
	}
	void init() {
		odt.clear();
		odt.insert({0,int(1e9),0});
		for(int i=1; i<=n; ++i) {
			add(l[i],r[i],i);
			tp[i]=op.size();
		}
	}
}
ll get_rank(int x) {
	ODT::clear();
	ll res=0;
	for(int i=1; i<=n; ++i) {
		ODT::ins(i);
		while(ODT::tot>=x) ODT::to_next();
		res+=ODT::lst;
	}
	return res;
}
ll get_ans(int lim) {
	ODT::clear();
	ll res=0;
	for(int i=1; i<=n; ++i) {
		ODT::ins(i);
		while(ODT::tot>=lim) ODT::to_next();
		res+=ll(ODT::lst)*ODT::tot+ODT::sum;
	}
	return res;
}
int main() {
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; ++i) scanf("%d%d",&l[i],&r[i]),--r[i];
	ODT::init();
	int l=1,r=1e9;
	while(l<=r) {
		int mid=(l+r)/2;
		if(get_rank(mid)<k) r=mid-1;
		else l=mid+1;
	}
	printf("%lld",get_ans(r+1)+(k-get_rank(r+1))*r);
	return 0;
}