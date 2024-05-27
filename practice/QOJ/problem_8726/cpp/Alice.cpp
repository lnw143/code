#include <vector>
#include <utility>
#include "Alice.h"

using namespace std;

vector<pair<int,int>> Alice(){
	const int n = 75;
    long long x = setN(n);
	vector<pair<int,int>> ans;
	for(int i=1; i<n; ++i)
		ans.emplace_back(make_pair(x%i+1,i+1));
    return ans;
}