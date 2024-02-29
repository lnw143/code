#include<cstdio>
using namespace std;
const int N(1e6), Q(3e5), S(N << 2), inf(1e9);
int n,m,q,i,a[N + 2],b[N + 2];
struct val {
	int mx,mn;
	val(int x=0,int y=0):mx(x),mn(y) {}
};
int min(int x,int y) {
	return x<y?x:y;
}
int max(int x,int y) {
	return x<y?y:x;
}
int abs(int x) {
	return x<0?-x:x;
}
val operator+(const val a,const val b) {
	return val(max(a.mx,b.mx),min(a.mn,b.mn));
}
struct Segtree {
	val tr[S + 2];
#define ls (x<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void modify(int x,int l,int r,int f,int g) {
		if(r<f||f<l) return ;
		if(l==r) {
			tr[x].mx=tr[x].mn=g;
			return ;
		}
		int mid=(l+r)/2;
		if(f<=mid) modify(li,f,g);
		else modify(ri,f,g);
		tr[x]=tr[ls]+tr[rs];
		return ;
	}
	val query(int x,int l,int r,int L,int R) {
		if(r<L||R<l) return val(-inf,inf);
		if(L<=l&&r<=R) return tr[x];
		int mid=(l+r)/2;
		return query(li,L,R)+query(ri,L,R);
	}
	int findmax(int x,int l,int r,int L,int R,int f) {
		if(r<L||R<l||tr[x].mx<f) return -1;
		if(l==r) return l;
		int mid=(l+r)/2;
		int rson=findmax(ri,L,R,f);
		return ~rson?rson:findmax(li,L,R,f);
	}
	int findmin(int x,int l,int r,int L,int R,int f) {
		if(r<L||R<l||tr[x].mx<f) return -1;
		if(l==r) return l;
		int mid=(l+r)/2;
		int lson=findmin(li,L,R,f);
		return ~lson?lson:findmin(ri,L,R,f);
	}
} row,col;
void read(int &x) {
	x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	do {
		x=(x<<3)+(x<<1)+(ch^'0');
		ch=getchar();
	} while(ch>='0'&&ch<='9');
	return ;
}
void write(int x) {
	if(x<0) {
		putchar('-');
		write(-x);
		return ;
	}
	static char buf[30];
	int len=0;
	do
		buf[len++]=x%10,
		           x/=10;
	while(x);
	while(len) putchar(buf[--len]^'0');
	putchar('\n');
}
int main() {
	freopen("snow.in","r",stdin);
	freopen("snow.out","w",stdout);
	read(n),read(m),read(q);
	for(i=1; i<=q; ++i) {
		static int op;
		read(op);
		if(op==1) {
			static int x;
			read(x);
			a[x]=i;
			row.modify(1,1,n,x,i);
		} else if(op==2) {
			static int x;
			read(x);
			b[x]=i;
			col.modify(1,1,m,x,i);
		} else {
			static int x1,y1,x2,y2,k;
			read(x1),read(y1),read(x2),read(y2),read(k);
			int ans=inf,tm=i-k;
			if(tm<=0) {
				write(abs(x1-x2)+abs(y1-y2));
				continue;
			}
#define askr(l,r) row.query(1,1,n,l,r)
#define askc(l,r) col.query(1,1,m,l,r)
			bool r1=a[x1]>=tm,c1=b[y1]>=tm,r2=a[x2]>=tm,c2=b[y2]>=tm;
			val c=askc(min(y1,y2),max(y1,y2)),r=askr(min(x1,x2),max(x1,x2));
			if(r1&&c2||r2&&c1) {
				write(abs(x1-x2)+abs(y1-y2));
				continue;
			}
			if(r1&&r2) {
				if(x1==x2||c.mx>=tm||r.mn>=tm) {
					write(abs(x1-x2)+abs(y1-y2));
					continue;
				}
				int l=min(y1,y2),r=max(y1,y2);
				int maxn=col.findmax(1,1,m,1,l-1,tm),minn=col.findmin(1,1,m,r+1,m,tm);
				if(~maxn) ans=min(ans,l-maxn);
				if(~minn) ans=min(ans,minn-r);
			}
			if(c1&&c2) {
				if(y1==y2||r.mx>=tm||c.mn>=tm) {
					write(abs(x1-x2)+abs(y1-y2));
					continue;
				}
				int l=min(x1,x2),r=max(x1,x2);
				int maxn=row.findmax(1,1,n,1,l-1,tm),minn=row.findmin(1,1,n,r+1,m,tm);
				if(~maxn) ans=min(ans,l-maxn);
				if(~minn) ans=min(ans,minn-r);
			}
			write(ans==inf?-1:ans*2+abs(x1-x2)+abs(y1-y2));
		}
	}
	return 0;
}