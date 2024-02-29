#include"testlib.h"
#include<cassert>
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
using vi = vector<int>;
#define read(type,name) name=opt<type>(#name);
int from,to,n,s,mid;
bool hack,balance;
vi len;
vi balance_len() {
	vi len(n);
	for(int i=0; i<n; ++i)
		len[i]=s/n+(i<s%n);
	return len;
}
vi rand_len() {
	vi len=balance_len();
	int sum=0;
	for(int &l : len) {
		l+=rnd.next(-5,5);
		sum+=l;
	}
	return sum<=s?len:rand_len();
}
string randStr(int len) {
	static char str[100];
	assert(len!=0);
	sprintf(str,"[a-z]{%d}",len);
	return rnd.next(str);
}
string randModify(string base,int add_len) {
	for(; add_len>0; --add_len) {
		int p=rnd.wnext(base.size()/2+1,mid);
		base=base.substr(0,p)+rnd.next("[a-z]")+base.substr(p,base.size()-p);
	}
	int randTime=rnd.next(10,15);
	for(; randTime>0; --randTime) {
		int p=rnd.wnext(base.size()/2+1,mid),q=rnd.wnext(base.size()/2,base.size()-1,-mid);
		base[p]=rnd.next("[a-z]")[0];
		base[q]=rnd.next("[a-z]")[0];
	}
	return base;
}
void Hack() {
	int min_len=*min_element(len.begin(),len.end());
	string base=randStr(min_len);
	for(int l : len)
		if(l<min_len) printf("%s\n",randStr(l).c_str());
		else printf("%s\n",randModify(base,l-min_len).c_str());
}
void Rand() {
	for(int l : len)
		printf("%s\n",randStr(l).c_str());
}
void writeTest(int test) {
	static char filename[100];
	sprintf(filename,"string%02d.in",test);
	freopen(filename,"wt",stdout);
	printf("%d\n",n);
	len=balance?balance_len():rand_len();
	return hack?Hack():Rand();
}
int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	read(int,from);
	read(int,to);
	read(int,n);
	read(int,s);
	assert(1<=n&&n<=s&&s<=1e6);
	read(bool,hack);
	if(hack) read(int,mid);
	read(bool,balance);
	for(int i=from; i<=to; ++i)
		writeTest(i);
	return 0;
}