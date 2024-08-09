#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int N = 1e6, B = 1e3;
struct node {
	node* nxt;
	vector<int> a;
	node():nxt(nullptr) {}
};
node* head=new node;
int n,q;
char s[N + 2];
int main() {
	scanf("%s",s+1);
	n=strlen(s+1);
	node* cur=head;
	for(int i=0; i<n/B; ++i) {
		for(int j=1; j<=B; ++j)
			cur->a.push_back(s[i*B+j]);
		cur->nxt=new node;
		cur=cur->nxt;
	}
	if(n%B)
		for(int i=n/B*B+1; i<=n; ++i)
			cur->a.push_back(s[i]);
	scanf("%d",&q);
	for(int i=1; i<=q; ++i) {
		char op;
		scanf(" %c",&op);
		if(op=='I') {
			char ch;
			int p;
			scanf(" %c%d",&ch,&p);
			--p;
			node *it=head;
			while(true) {
				if(p>it->a.size()) {
					p-=it->a.size();
					it=it->nxt;
					continue;
				}
				it->a.insert(it->a.begin()+p,ch);
				if(it->a.size()>=B*2) {
					node *tmp=new node;
					tmp->nxt=it->nxt;
					tmp->a=vector<int>(it->a.begin()+B,it->a.end());
					for(int j=1; j<=B; ++j) it->a.pop_back();
					it->nxt=tmp;
				}
				break;
			}
		} else {
			int p;
			scanf("%d",&p);
			node *it=head;
			while(true) {
				if(p>it->a.size()) {
					p-=it->a.size();
					it=it->nxt;
					continue;
				}
				printf("%c\n",it->a[p-1]);
				break;
			}
		}
	}
	return 0;
}