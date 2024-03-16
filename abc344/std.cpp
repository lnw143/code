#include<bits/stdc++.h>

using namespace std;
using pl=pair<long long,long long>;
using ppl=pair<pl,long long>;

long long g;
long long md=((1ll<<31)-1);
long long gen(){
  g = (48271*g) % md;
  return g;
}

long long comp_pl(pl a,pl b){
  long long l=a.first*b.second;
  long long r=a.second*b.first;
  if(l<r){return -1;}
  if(l>r){return 1;}
  return 0;
}

int main(){
	freopen(".in","r",stdin);
	freopen(".ans","w",stdout);
  long long n;
  cin >> n;
  vector<pl> p(n);
  for(long long i=0;i<n;i++){
    cin >> p[i].first >> p[i].second;
  }
  sort(p.begin(),p.end());

  priority_queue<ppl,vector<ppl>,decltype(
    [](ppl a,ppl b){
      long long cp=comp_pl(a.first,b.first);
      if(cp==0){return (a.second>b.second);}
      if(cp==-1){return false;}
      return true;
    }
  )> pq;

  for(long long i=1;i<n;i++){
    if(p[i-1].first<p[i].first){
      ppl x;
      x.first={p[i].second-p[i-1].second,p[i].first-p[i-1].first};
      x.second=i;
      pq.push(x);
    }
  }

  long long q,ra,rb;
  cin >> q >> g >> ra >> rb;

  vector<pl> ask;
  for(long long i=0;i<q;i++){
    long long g1=gen();
    long long g2=gen();
    long long g3=gen();

    long long a = -ra + (g1%(2*ra+1));
    long long b = -rb + ((g2*md+g3)%(2*rb+1));
    ask.push_back({a,b});
  }

  sort(ask.begin(),ask.end());

  long long res=0;
  for(long long ak=0;ak<q;ak++){
    long long a=ask[ak].first;
    long long b=ask[ak].second;
    while(!pq.empty()){
      ppl od=pq.top();
      long long i=od.second;
      if(
        od.first!=make_pair(p[i].second-p[i-1].second,p[i].first-p[i-1].first)
      ){pq.pop();continue;}

      pl cp=od.first;
      pl cd={a,1};
      if(comp_pl(cp,cd)!=-1){break;}

      pq.pop();
      swap(p[i-1],p[i]);
      i--;
      if(i>0 && p[i-1].first<p[i].first){
        ppl x;
        x.first={p[i].second-p[i-1].second,p[i].first-p[i-1].first};
        x.second=i;
        pq.push(x);
      }
      i+=2;
      if(i<n && p[i-1].first<p[i].first){
        ppl x;
        x.first={p[i].second-p[i-1].second,p[i].first-p[i-1].first};
        x.second=i;
        pq.push(x);
      }
    }

    long long l=0,r=n-1;
    while(l<=r){
      long long te=(l+r)/2;
      if(p[te].second >= a*p[te].first+b){r=te-1;}
      else{l=te+1;}
    }

    res+=(n-1-r);
  }

  cout << res << "\n";
  return 0;
}
