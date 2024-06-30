#include <iostream>
#include <string>
using namespace std;
string a;
int main() {
	cin>>a;
	for(auto c : a)
		if(c=='R') {
			cout<<"Yes\n";
			return 0;
		} else if(c=='M') {
			cout<<"No\n";
			return 0;
		}
	return 0;
}