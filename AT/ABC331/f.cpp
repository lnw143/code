#include<cstdio>
#define ls (x<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
using llu = long long unsigned;
const int N = 1e6 + 2;
int n,i,q,o,a,b;
llu w[N];
char s[N],ch;
struct Tree {
	int s;
	llu x;
	Tree operator+(const Tree t) const {
		return {s+t.s, x*w[t.s]+t.x};
	}
	bool operator==(const Tree t) const {
		return s==t.s&&x==t.x;
	}
} tr[N * 4],tr2[N * 4];
void mk(int x,int l,int r) {
	if(l==r) {
		tr2[x]=tr[x]= {1, s[l]-'a'};
		return ;
	}
	int mid=(l+r)/2;
	mk(li);
	mk(ri);
	tr[x]=tr[ls]+tr[rs];
	tr2[x]=tr2[rs]+tr2[ls];

}
void cg(int x,int l,int r,int h,int f) {
	if(r<h||h<l) return ;
	if(l==r) {
		tr2[x]=tr[x]= {1, f};
		return ;
	}
	int mid=(l+r)/2;
	if(h<=mid) cg(li,h,f);
	else cg(ri,h,f);
	tr[x]=tr[ls]+tr[rs];
	tr2[x]=tr2[rs]+tr2[ls];
}
Tree qr(int x,int l,int r,int L,int R) {
	if(r<L||R<l) return {0, 0};
	if(L<=l&&r<=R) return tr[x];
	int mid=(l+r)/2;
	return qr(li,L,R)+qr(ri,L,R);
}
Tree qr2(int x,int l,int r,int L,int R) {
	if(r<L||R<l) return {0, 0};
	if(L<=l&&r<=R) return tr2[x];
	int mid=(l+r)/2;
	return qr2(ri,L,R)+qr2(li,L,R);
}
int main() {
	scanf("%d%d%s",&n,&q,s+1);
	w[0]=1;
	for(i=1; i<=n; ++i)
		w[i]=w[i-1]*131;
	mk(1,1,n);
	for(i=1; i<=q; ++i) {
		scanf("%d",&o);
		if(o==1) {
			scanf("%d %c",&a,&ch);
			cg(1,1,n,a,ch-'a');
		} else {
			scanf("%d%d",&a,&b);
			int mid=(a+b)/2;
			printf(qr(1,1,n,a,mid)==qr2(1,1,n,mid+(a%2!=b%2),b)?"Yes\n":"No\n");
		}
	}
	return 0;
}