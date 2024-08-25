#include<bits/stdc++.h>
#define ll long long
using namespace std;

void setResult(double score) // 输出测试结果
{
	printf("%0.1lf\n", score); // 输出分数
	exit(0); // 结束程序运行，程序返回值应为0
}

char s1[1145],s2[1145];
ll c[310][310],vis[310*310];

struct BIT
{
	int c[310*310],n;
	void clear(){memset(c,0,sizeof(c));}
	inline int lowbit(int x){return x&(-x);}
	void add(int u,int x)
	{
		for (int i=u;i<=n;i+=lowbit(i))
			c[i]+=x;
	}
	int ask(int u)
	{
		int res=0;
		for (int i=u;i>=1;i-=lowbit(i))res+=c[i];
		return res;
	}
}t;

int main(int argc, const char *argv[])
{
	const char *inF = argv[1];// 输入文件
	const char *ouF = argv[2];// 被测试者的输出文件
	const char *stdF = argv[3];// 命题人的参考输出
//	const char *logF = argv[4];// 检验结果

//	freopen(logF, "w", stdout); // 直接打开结果文件，使用标准输出
	
//	double vu, vs; // 用于记录被测试者的输出和参考输出
	FILE *fout = fopen(ouF, "r"); // 打开被测试者的输出
	if (!fout)
		setResult(0.0);
	FILE *fstd = fopen(stdF, "r"); // 打开命题人的参考输出
	if (!fstd)
		setResult(0.0);
	FILE *fin = fopen(inF, "r"); // 打开命题人的参考输出
	if (!fin)
		setResult(0.0);
	int T;fscanf(fin,"%d",&T);
	double ans=1.0;
	while(T--)
	{
		ll n,X,Y;fscanf(fin,"%lld%lld%lld",&n,&X,&Y);
		fscanf(fout,"%s",s1),fscanf(fstd,"%s",s2);
		if (s2[0]=='N')
		{
			if (s1[0]!=s2[0]||s1[1]!=s2[1])setResult(0);
			continue;
		}
		if (s1[0]!=s2[0]||s1[1]!=s2[1]||s1[2]!=s2[2])setResult(0);
		memset(vis,0,sizeof(vis));
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
			{
				fscanf(fout,"%lld",&c[i][j]);
				if (c[i][j]>n*n||c[i][j]<1||vis[c[i][j]])setResult(0);
				vis[c[i][j]]=1;
			}
		t.clear(),t.n=n*n;ll s=0;
		for (int i=n;i>=1;i--)for (int j=n;j>=1;j--)
			s+=t.ask(c[i][j]),t.add(c[i][j],1);
		if (s!=X)ans=min(ans,0.2);
//		cerr<<n<<' '<<X<<' '<<Y<<' '<<s<<' ';
		s=0;t.clear();
		for (int i=n;i>=1;i--)for (int j=n;j>=1;j--)
			s+=t.ask(c[j][i]),t.add(c[j][i],1);
		if (s!=Y)ans=min(ans,0.2);
//		cerr<<s<<'\n'; 
	}
//	while (true) {
//		int tu = fscanf(fout, "%lf", &vu); // 读被测试者的结果
//		int ts = fscanf(fstd, "%lf", &vs); // 读参考输出
//		if ((tu>0) ^ (ts>0)) { // 元素个数不同
//			setResult(0.0); // 错误
//		}
//		if (!(tu>0)) break;
//		double delta = vu - vs; // 绝对误差
//		if (vs>1 || vs<-1) // 相对误差更小
//			delta /= vs; // 相对误差
//		if (delta < 0)
//			delta = -delta; // 绝对值
//		if (!(delta<=EPS)) // 比较被测试者的输出和参考输出
//			setResult(0.0); // 错误
//	}

	fclose(fout);
	fclose(fstd);
	setResult(ans); // 正确

	return 0;
}

