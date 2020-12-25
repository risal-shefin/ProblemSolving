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



vector < pair < ll,ll > > vec;
pair < ll,ll > pr;
ll ara[500002],trck[500005],tree[2000002];
vector < ll > tmp[500002];
stack < ll > st;

ll qry(ll node,ll l,ll r,ll p)
{
    if(l>p)return 0;
    if(r<=p)return tree[node];
    ll ln=node*2,mid=(l+r)/2;
    ll a = qry(ln,l,mid,p);
    ll b = qry(ln+1,mid+1,r,p);
    return max(a,b);
}

void up(ll node,ll l,ll r,ll i,ll x)
{
    if(i>r||i<l){
        return;
    }
    if(l==r){
        tree[node]+=x;
        return;
    }
    ll ln=node*2;
    ll rn=ln+1,mid=(l+r)/2;
    up(ln,l,mid,i,x);
    up(ln+1,mid+1,r,i,x);
    tree[node]=max(tree[ln],tree[rn]);
    return;
}

int main()
{
    ll test,t,i,j,k,a,b,c,x,y,z,n,m;
    scl(test);
    for(t=1;t<=test;t++)
    {
        scl(n);
        for(i=1;i<=n;i++){
            scl(ara[i]);
            vec.pb(mp(ara[i],i));
            tmp[i].clear();
        }
        sort(vec.begin(),vec.end());
        for(i=0;i<n;i++){
            pr=vec[i];
            trck[pr.sc]=i+1;
        }
        for(i=n;i>0;i--){
            while(!st.empty()){
                a=st.top();
                if(ara[a]<ara[i]){
                    st.pop();
                }
                else break;
            }
            if(!st.empty()){
                a=st.top();
                //cout<<i << "   " <<a<<endl;
                tmp[a].pb(trck[i]);
            }
            st.push(i);
        }
        for(i=1;i<=n;i++){
            a=trck[i];
            b=qry(1,0,n,a-1);
            b++;
            if(i>1){
                b=max(b,2ll);
            }
            //cout<<i<< " "<<a<< " " <<b<<endl;
            up(1,0,n,a,b);
            for(j=0;j<tmp[i].size();j++){

                x=tmp[i][j];
                //cout<<x<<endl;
                up(1,0,n,x,1);
            }
        }
        printf("%lld\n",tree[1]);
        vec.clear();
        while(!st.empty())st.pop();
        for(i=0;i<=4*n;i++){
            tree[i]=0;
        }
    }

    return 0;
}

