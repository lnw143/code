template<int N,int logN,class _Tp,_Tp max(_Tp,_Tp)> struct RMQ {
	int n,m,B;
	_Tp a[N + 2],pre[N + 2],suf[N + 2],st[logN][N/logN + 2];
	unsigned long long sta[N + 2];
	inline int belong(int p) {
		return (p-1)/B+1;
	}
	inline int pos(int p) {
		return (p-1)%B;
	}
	void init(int len,_Tp *_a) {
		n=len;
		B=1.5*log2(n);
		if(B<1) B=1;
		for(int i=1; i<=n; ++i) a[i]=_a[i];
		for(int i=1; i<=n; ++i)
			if(pos(i)==0)
				pre[i]=a[i];
			else
				pre[i]=max(pre[i-1],a[i]);
		suf[n]=a[n];
		for(int i=n-1; i>=1; --i)
			if(i%B==0)
				suf[i]=a[i];
			else
				suf[i]=max(suf[i+1],a[i]);
		m=belong(n);
		for(int i=1; i<=m; ++i)
			st[0][i]=suf[(i-1)*B+1];
		for(int j=1; j<logN; ++j)
			for(int i=1; i+(1<<j)-1<=m; ++i)
				st[j][i]=max(st[j-1][i],st[j-1][i+(1<<(j-1))]);
		static int stk[N + 2];
		for(int i=1,tp=0; i<=n; ++i) {
			if(pos(i)==0) tp=0;
			else sta[i]=sta[i-1];
			unsigned long long &s=sta[i];
			while(tp&&max(a[i],a[stk[tp]])==a[i])
				s^=1llu<<pos(stk[tp]),--tp;
			stk[++tp]=i;
			s|=1llu<<pos(i);
		}
	}
	_Tp queryBlock(int l,int r) {
		int k=__lg(r-l+1);
		return max(st[k][l],st[k][r-(1<<k)+1]);
	}
	_Tp query(int l,int r) {
		int x=belong(l),y=belong(r);
		if(x<y) {
			_Tp res=max(suf[l],pre[r]);
			if(x+1<y) res=max(res,queryBlock(x+1,y-1));
			return res;
		} else
			return a[l+__builtin_ctzll(sta[r]>>pos(l))];
	}
};