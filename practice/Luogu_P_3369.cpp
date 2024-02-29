#include<cstdio>
#include<random>
#define rep(i,l,r) for(int i(l),i##END(r); i<=i##END; ++i)
#define per(i,l,r) for(int i(r),i##END(l); i>=i##END; --i)
using namespace std;
mt19937 rnd(random_device{}());
const int N(1e5);
namespace treap {
	int tot;
	struct Node {
		int ls,rs,val,siz,cnt,pri;
	} tr[N + 2];
#define ls(x) tr[x].ls
#define rs(x) tr[x].rs
#define val(x) tr[x].val
#define siz(x) tr[x].siz
#define cnt(x) tr[x].cnt
#define pri(x) tr[x].pri
	int newnode(int v) {
		++tot;
		val(tot)=v;
		siz(tot)=cnt(tot)=1;
		pri(tot)=rnd();
	}
	void insert(int x) {
		
	}
}
int n;
int main() {
	
	return 0;
}