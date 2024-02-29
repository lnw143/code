#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int N(1e2), M(1e3);
using db = double;
template<int n,int m>
struct Matrix {
	public:
		db* operator[](const int y) {
			return x[y];
		}
		Matrix() {
			memset(x,0,sizeof(x));
		}
	private:
		db x[n + 2][m + 2];
};
template<int n,int m,int k> Matrix<n,k> operator*(Matrix<n,m> a,Matrix<m,k> b) {
	Matrix<n,k> c;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			for(int l=1; l<=k; ++l)
				c[i][l]+=a[i][j]*b[j][l];
	return c;
}
using Pos = Matrix<3,1>;
using Trans = Matrix<3,3>;
int n,tp,v[M + 2];
Pos p[N + 2];
Trans ori,stk[M];
char op[M];
void trans(db x,db y) {
	Trans t=ori;
	t[1][3]=x;
	t[2][3]=y;
	stk[tp]=t*stk[tp];
}
void scale(db x,db y) {
	Trans t=ori;
	t[1][1]=x;
	t[2][2]=y;
	stk[tp]=t*stk[tp];
}
void rotate(db theta) {
	db Sin=sin(theta),Cos=cos(theta);
	Trans t;
	t[1][1]=t[2][2]=Cos;
	t[1][2]=-Sin;
	t[2][1]=Sin;
	t[3][3]=1;
	stk[tp]=t*stk[tp];
}
Trans qpow(Trans a,int n) {
	Trans x=ori;
	for(; n; n>>=1,a=a*a)
		if(n&1)
			x=x*a;
	return x;
}
int main() {
	freopen("transform.in","r",stdin);
	freopen("transform.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		scanf("%lf%lf",&p[i][1][1],&p[i][2][1]);
		p[i][3][1]=1;
	}
	ori[1][1]=ori[2][2]=ori[3][3]=1;
	stk[0]=ori;
	while(scanf(" %s",op)==1)
		switch(*op) {
			case 'T': {
				db x,y;
				sscanf(op,"Trans(%lf,%lf)",&x,&y);
				trans(x,y);
				break;
			}
			case 'S': {
				db x,y;
				sscanf(op,"Scale(%lf,%lf)",&x,&y);
				scale(x,y);
				break;
			}
			case 'R': {
				db theta,x,y;
				sscanf(op,"Rotate(%lf,%lf,%lf)",&theta,&x,&y);
				trans(-x,-y);
				rotate(-theta);
				trans(x,y);
				break;
			}
			case 'L': {
				stk[++tp]=ori;
				sscanf(op,"Loop(%d)",&v[tp]);
				break;
			}
			case 'E': {
				stk[tp-1]=qpow(stk[tp],v[tp])*stk[tp-1];
				--tp;
				break;
			}
		}
	for(int i=1; i<=n; ++i) {
		p[i]=stk[0]*p[i];
		printf("%.4lf %.4lf\n",p[i][1][1],p[i][2][1]);
	}
	return 0;
}