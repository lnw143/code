#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 1e5, M = 1e5, V = N + M;
int n,m,cnt,a[N + 2],ans[M + 2];
vector<int> num,pos[V + 2];
struct query {
	int type,x,y,k;
	query(int l,int r,int k):type(1),x(l),y(r),k(k) {}
	query(int x,int y):type(2),x(x),y(y) {}
	query()=default;
} q[M + 2];
struct operation {
	int type,x,y,k;
	operation(int ind,int l,int r,int k):type(ind),x(l),y(r),k(k) {}
	operation(int x,int y,bool add):type(add?-1:-2),x(x),y(y),k(0) {}
	operation()=default;
} op[N + M * 2 + 2];
namespace fenwick {
	int s[N + 2];
	void add(int x,int v) {
		for(; x<=n; x+=x&-x) s[x]+=v;
	}
	int sum(int x) {
		int r=0;
		for(; x; x&=x-1) r+=s[x];
		return r;
	}
	int sum(int l,int r) {
		return sum(r)-sum(l-1);
	}
}
void solve(int l,int r,vector<int> Q) {
	if(Q.empty()) return ;
	if(l==r) {
		for(auto i : Q)
			if(op[i].type>0)
				ans[op[i].type]=l;
		return ;
	}
	int mid=(l+r)/2;
	vector<int> Ql,Qr;
	for(auto i : Q)	{
		auto& [type,x,y,k]=op[i];
		if(type>0) {
			int res=fenwick::sum(x,y);
			if(res>=k) Ql.push_back(i);
			else {
				k-=res;
				Qr.push_back(i);
			}
		} else if(y<=mid) {
			Ql.push_back(i);
			fenwick::add(x,type==-1?1:-1);
		} else
			Qr.push_back(i);
	}
	for(auto i : Q)
		if(op[i].type<0&&op[i].y<=mid)
			fenwick::add(op[i].x,op[i].type==-1?-1:1);
	solve(l,mid,Ql);
	solve(mid+1,r,Qr);
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	for(int i=1; i<=m; ++i) {
		char c;
		scanf(" %c",&c);
		if(c=='Q') {
			int l,r,k;
			scanf("%d%d%d",&l,&r,&k);
			q[i]=query(l,r,k);
		} else {
			int x,y;
			scanf("%d%d",&x,&y);
			q[i]=query(x,y);
		}
	}
	for(int i=1; i<=n; ++i) num.push_back(a[i]);
	for(int i=1; i<=m; ++i) if(q[i].type==2) num.push_back(q[i].y);
	sort(num.begin(),num.end());
	num.erase(unique(num.begin(),num.end()),num.end());
	for(int i=1; i<=n; ++i) a[i]=lower_bound(num.begin(),num.end(),a[i])-num.begin()+1;
	for(int i=1; i<=m; ++i) if(q[i].type==2) q[i].y=lower_bound(num.begin(),num.end(),q[i].y)-num.begin()+1;
	for(int i=1; i<=n; ++i) pos[a[i]].push_back(i);
	for(int i=1; i<=n; ++i) op[++cnt]=operation(i,a[i],true);
	for(int i=1; i<=m; ++i) {
		if(q[i].type==1)
			op[++cnt]=operation(i,q[i].x,q[i].y,q[i].k);
		else {
			op[++cnt]=operation(q[i].x,a[q[i].x],false);
			op[++cnt]=operation(q[i].x,q[i].y,true);
			a[q[i].x]=q[i].y;
		}
	}
	vector<int> Q;
	for(int i=1; i<=cnt; ++i) Q.push_back(i);
	solve(1,num.size(),Q);
	for(int i=1; i<=m; ++i)
		if(q[i].type==1)
			printf("%d\n",num[ans[i]-1]);
	return 0;
}