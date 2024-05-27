#include<iostream>
using namespace std;
using ll = long long;
const int N(1e7), P(1e9 + 7);
int n;
ll ans;
string s[N + 2];
int lcp(string a,string b) {
	for(int i=0; i<a.size()&&i<b.size(); ++i)
		if(a[i]!=b[i])
			return i;
	return min(a.size(),b.size());
}
int lcs(string a,string b) {
	for(int i=1; i<=a.size()&&i<=b.size(); ++i)
		if(a[a.size()-i]!=b[b.size()-i])
			return i-1;
	return min(a.size(),b.size());
}
int main() {
	cin>>n;
	for(int i=1; i<=n; ++i)
		cin>>s[i];
	for(int i=1; i<n; ++i)
		for(int j=i+1; j<=n; ++j)
			ans=(ans+(ll)lcs(s[i],s[j])*lcp(s[i],s[j])%P)%P;
	printf("%d",ans);
	return 0;
}