#include<cstdio>
#include<cstdlib>
using namespace std;
int main() {
    while(true) {
        system("./data");
        system("./bf");
        system("./tree");
        if(system("diff ./tree.out ./tree.ans")) {
            break;
        }
    }
    return 0;
}