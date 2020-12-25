#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back
#define sc second
#define fr first
#define scl(n) scanf("%lld",&n)
#define scll(n,m) scanf("%lld%lld",&n,&m)
#define scs(ch) scanf("%s", ch)
#define pll pair<ll,ll>

map < pll, ll > cnt;

int main()
{
    ll test,t,i,j,k,a,b,c,x,y,z,n,m,p,q,inf =2e9,u,v;
    scl(test);
    for(t=1;t<=test;t++){
        scl(n);
        z=0;
        for(i=1;i<=n;i++){
            scll(a,b);
            scll(x,y);
            p=x-a;
            q=y-b;
            if(p==0){
                if(q<0)
                    q=-inf;
                else
                    q=inf;
            }
            else if(q==0)
            {
                if(p<0)
                    p=-inf;
                else
                    p=inf;
            }
            else{
                c=__gcd(p,q);
                c=abs(c);
                //printf("gcd= %lld",c);
                p/=c;
                q/=c;
            }
            //cout<<p<< " " <<q<<endl;
            u=-p;
            v=-q;
            //cout<< u << "    " <<v<<endl;
            z+=cnt[mp(u,v)];
            //cout<<z<<endl;
            cnt[mp(p,q)]++;
        }
        printf("%lld\n",z);
        cnt.clear();
    }
    return 0;
}

