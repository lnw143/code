#include <cstdio>
using namespace std;
int main() {
	freopen("template.cpp","r",stdin);
	freopen("string.txt","w",stdout);
	char c;
	while((c=getchar())!=EOF) {
		if(c=='\n') printf("\\n");
		else if(c=='\t') printf("\\t");
		else if(c=='"') printf("\\\"");
		else if(c=='\\') printf("\\\\");
		else putchar(c);
	}
	return 0;
}