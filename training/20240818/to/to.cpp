#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
using ll = long long;
const int N = 1e4, M = 5e3, P = 1e9 + 7;
int n,m,k;
char s[N + 2];
string stk,ep;
vector<int> num;
void pop() {
	if(num.back()) ep+='_';
	num.pop_back();
	if(num.back()) ep+='_';
	num.pop_back();
	ep+=stk.back();
	stk.pop_back();
	num.push_back(0);
}
bool bz[M + 2];
int p[M + 2],ans;
void solve() {
	vector<int> stk;
	int i=0;
	for(auto c : ep)
		switch(c) {
			case '_': {
				stk.push_back(p[++i]);
				break;
			}
			case '+': {
				int a=stk.back();
				stk.pop_back();
				int b=stk.back();
				stk.pop_back();
				stk.push_back((a+b)%P);
				break;
			}
			case '*': {
				int a=stk.back();
				stk.pop_back();
				int b=stk.back();
				stk.pop_back();
				stk.push_back((ll)a*b%P);
			}
		}
	ans=(ans+stk[0])%P;
}
void dfs(int u) {
	if(u>k) {
		solve();
		return ;
	}
	for(int i=1; i<=m; ++i)
		if(!bz[i]) {
			bz[i]=true;
			p[u]=i;
			dfs(u+1);
			bz[i]=false;
		}
}
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
int main() {
	freopen("to.in","r",stdin);
	freopen("to.out","w",stdout);
	scanf("%d%s",&m,s+1);
	n=strlen(s+1);
	k=count(s+1,s+n+1,'_');
	if(count(s+1,s+n+1,'*')==0) {
		ll t=k;
		for(int i=m-k+1; i<m; ++i) t=t*i%P;
		for(int i=1; i<=m; ++i) ans=(ans+t*i%P)%P;
	} else {
		for(int i=1; i<=n; ++i)
			switch(s[i]) {
				case '+': {
					while(stk.size()&&stk.back()=='*') pop();
					stk+='+';
					break;
				}
				case '(': {
					stk+='(';
					break;
				}
				case ')': {
					while(stk.back()!='(') pop();
					stk.pop_back();
					break;
				}
				case '_': {
					num.push_back(1);
					break;
				}
				case '*': {
					stk.push_back('*');
					break;
				}
			}
		while(stk.size()) pop();
		dfs(1);
	}
	ll r=1;
	for(int i=m-k+1; i<=m; ++i) r=r*i%P;
	printf("%lld",ans*qpow(r,P-2)%P);
	return 0;
}