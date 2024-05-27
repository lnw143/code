#include<cstdio>
using namespace std;
int T,M,a,b,c,delta,sq;
int get_sq(int x) {
	int s=1;
	for(int i=2; i*i<=x; ++i)
		while(x%(i*i)==0) {
			x/=i*i;
			s*=i;
		}
	return x?s:0;
}
int gcd(int a,int b) {
	int r=a%b;
	while(r) {
		a=b;b=r;
		r=a%b;
	}
	return b;
}
void print(int q,int p) {
	int g=gcd(q,p);
	q/=g,p/=g;
	if(p<0) q=-q,p=-p;
	if(p!=1)
		printf("%d/%d",q,p);
	else
		printf("%d",q);
}
void work(int dt,int p) {
	int s=sq,g=gcd(s,p);
	s/=g,p/=g;
	if(s!=1) printf("%d*",s);
	printf("sqrt(%d)",dt/sq/sq);
	if(p!=1) printf("/%d",p);
	return ;
}
int main() {
	freopen("uqe.in","r",stdin);
	freopen("uqe.out","w",stdout);
	scanf("%d%d",&T,&M);
	while(T--) {
		scanf("%d%d%d",&a,&b,&c);
		delta=b*b-4*a*c;
		if(delta<0) {
			printf("NO\n");
			continue;
		}
		sq=get_sq(delta);
		if(sq*sq==delta) {
			if(delta==0||a>0)
				print(-b+sq,2*a);
			else
				print(b+sq,-2*a);
		} else {
			if(b) {
				print(-b,2*a);
				putchar('+');
			}
			work(delta,a<0?-2*a:2*a);
		}
		putchar('\n');
	}
	return 0;
}
