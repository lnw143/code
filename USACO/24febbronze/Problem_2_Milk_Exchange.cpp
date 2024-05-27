#include<cstdio>
#include<vector>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vii = vector<vi>;
const int N(2e5);
int n,m,a[N + 2];
ll ans;
char s[N + 2],t[N + 2];
bool bz[N + 2];
vii find(char c) {
	vii pos;
	for(int i=1; i<=n; ++i)
		if(s[i]==c&&!bz[i]) {
			if(s[i-1]!=c||bz[i-1]) pos.push_back(vi());
			(*pos.rbegin()).push_back(a[i]);
		}
	return pos;
}
int pos(int p) {
	return (p+n)%n+1;
}
int main() {
	scanf("%d%d%s",&n,&m,t+1);
	int turn=1;
	for(int i=1; i<n; ++i)
		if(t[i]=='L'&&t[i+1]=='R') {
			turn=i+1;
			break;
		}
	for(int i=1; i<=n; ++i)
		s[pos(i-turn)]=t[i];
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[pos(i-turn)]),ans+=a[pos(i-turn)];
	if(s[1]==s[n]) {
		printf("%lld",ans);
		return 0;
	}
	for(int i=1; i<=n; ++i)
		if(s[i]=='R'&&s[i%n+1]=='L')
			bz[i]=bz[i%n+1]=true;
	for(vi v : find('L')) {
		int remain=m;
		for(auto it=v.rbegin(); it!=v.rend(); ++it)
			if(remain>=*it) {
				remain-=*it;
				ans-=*it;
			} else {
				ans-=remain;
				break;
			}
	}
	for(vi v : find('R')) {
		int remain=m;
		for(auto it=v.begin(); it!=v.end(); ++it)
			if(remain>=*it) {
				remain-=*it;
				ans-=*it;
			} else {
				ans-=remain;
				break;
			}
	}
	printf("%lld",ans);
	return 0;
}