#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <deque>
#define STR_SIZE 10000

FILE *fpin, *fpout;

void open_files(char *in, char *out)
{
	if ((fpin = fopen (in, "r")) == NULL) {
		printf ("Can not open input file!\n");
		exit(0);
	}

	if ((fpout = fopen (out, "r")) == NULL) {
		printf ("Can not open player's output file!\n");
		exit(0);
	}
}

int a[2222222];
std::deque<int> q[333];

void specialJudge(FILE *in, FILE *out){
	int T;
	int n,m,k,Case;
	fscanf(in, "%d", &T);
	for(Case=1;Case<=T;Case++) {
		fscanf(in, "%d%d%d", &n,&m,&k);
		for(int i=1;i<=m;++i){
			fscanf(in, "%d", a+i);
		}
		int now=1;
		int op;
		if(fscanf(out, "%d", &op)!=1){
			printf ("Wrong Answer: Output type wrong in Test %d\n", Case);
			exit(0);
		}
		if(op<m||op>2*m){
			printf ("Wrong Answer: The num of opt: %d < %d or %d > 2 * %d in Test %d\n", op, m, op, m, Case);
			exit(0);
		}
		for(int i=1;i<=op;++i){
			int v,s1,s2;
			if(fscanf(out, "%d", &v)!=1){
				printf ("Wrong Answer: Output type wrong in Test %d,%d\n", Case, i);
				exit(0);
			}
			if(v==1){
				if(fscanf(out, "%d", &s1)!=1){
					printf ("Wrong Answer: Output type wrong in Test %d,%d,1\n", Case, i);
					exit(0);
				}
				if(s1<=0||s1>n){
					printf ("Wrong Answer: Output out of bounds in Test %d,%d,1 \"1 %d\"\n", Case, i, s1);
					exit(0);
				}
				if(now<=m){
					if(!q[s1].empty()&&a[now]==q[s1].back()){
						q[s1].pop_back();
					}
					else{
						q[s1].push_back(a[now]);
					}
					++now;
				}
			}
			else if(v==2){
				if(fscanf(out, "%d%d", &s1, &s2)!=2){
					printf ("Wrong Answer: Output type wrong in Test %d,%d,2\n", Case,i);
					exit(0);
				}
				if(s1<=0||s1>n||s2<=0||s2>n||s1==s2){
					printf ("Wrong Answer: Output out of bounds in Test %d,%d,2 \"2 %d %d\"\n", Case,i, s1,s2);
					exit(0);
				}
				if(!q[s1].empty()&&!q[s2].empty()&&q[s1].front()==q[s2].front()){
					q[s1].pop_front();
					q[s2].pop_front();
				}
			}
			else {
				printf ("Wrong Answer: Output type wrong in Test %d,%d \"%d\"\n", Case,i,v);
				exit(0);
			}
		}
		if(now<=m){
			printf ("Wrong Answer: There are some cards still in your hand in Test %d\n", Case);
			printf ("The cards in your hand: ");
			for(int i = now; i <= m; i++) {
				printf("%d ", a[i]);
			}
			exit(0);
		}
		for(int i=1;i<=n;++i){
			if(q[i].size()){
				printf ("Wrong Answer: There are some cards still in the stack in Test %d\n", Case);
				printf ("The cards in the stack:\n");
				for(int j = 1; j <= n; j++) {
					printf("Stack %d: ", j);
					for(auto v : q[j]) {
						printf("%d ", v);
					}
					printf("\n");
				}
				exit(0);
			}
		}
	}
}

int main (int argc, char *argv[])
{
	if (argc != 3) {
		printf ("Invalid Call!\nUsage: checker <in> <out>\n");
		return 0;
	}

	open_files (argv[1], argv[2]);

	specialJudge(fpin, fpout);
	printf ("Right Output!!!\n");
	return 0;
}
