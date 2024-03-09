#include<cstdio>
#include<map>
using namespace std;
const int N(2e5);
int n,q,a[N];
struct Node {
	int x;
	Node *pre,*nxt;
	void del() {
		if(pre!=nullptr) pre->nxt=nxt;
		if(nxt!=nullptr) nxt->pre=pre;
	}
	Node():x(0),pre(nullptr),nxt(nullptr) {}
};
map<int,Node*> mp;
void dfs(Node *p) {
	if(p==nullptr) return ;
	printf("%d ",p->x);
	dfs(p->nxt);
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
		Node *p=new Node;
		mp[a[i]]=p;
		p->x=a[i];
	}
	for(int i=2; i<=n; ++i)
		mp[a[i]]->pre=mp[a[i-1]];
	for(int i=1; i<n; ++i)
		mp[a[i]]->nxt=mp[a[i+1]];
	scanf("%d",&q);
	for(int i=1; i<=q; ++i) {
		int op,x,y;
		scanf("%d%d",&op,&x);
		if(op==1) {
			scanf("%d",&y);
			Node *p=new Node;
			p->x=y;
			p->pre=mp[x];
			p->nxt=mp[x]->nxt;
			if(mp[x]->nxt) mp[x]->nxt->pre=p;
			mp[x]->nxt=p;
			mp[y]=p;
		} else {
			mp[x]->del();
			mp.erase(x);
		}
	}
	for(auto [u,v] : mp)
		if(v->pre==nullptr) {
			dfs(v);
			break;
		}
	return 0;
}