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
#define pll pair< ll,ll >

set < ll > st;
set < ll > :: iterator it;

ll dp[100005][12][3],ara[100004],lst[12],tmp[12][2];

long double trck[12],val[100005][12],tmpval[12];


vector < ll > vec;

void prn(ll a,ll b)
{
    if(a==0){
        return;
    }
    vec.pb(a);
    prn(dp[a][b][0],dp[a][b][1]);

    return;
}

int main()
{
    ll test,t,i,j,k,a,b,c,x,y,z,n,m;

    scl(n);
    scl(m);

    for(i=1;i<=n;i++){
        scl(ara[i]);
    }

    for(i=1;i<=n;i++)
    {
        a=ara[i];
        long double aa = log10((double)a),bb,cc;

        b=a%10;

        for(j=0;j<=10;j++){
            tmpval[j]=0.0;
        }
        if(aa>tmpval[b] && aa>trck[b])
        {
            tmpval[b]=aa;
            tmp[b][0]=0;
            tmp[b][1]=10;
        }

        for(j=0;j<10;j++)
        {
            if(lst[j]==0)continue;
            bb=aa+trck[j];
            x=(j*b)%10;

            if(bb>tmpval[x] && bb>trck[x]){

                tmpval[x]=bb;
                tmp[x][0]=lst[j];
                tmp[x][1]=j;

            }
        }

        for(j=0;j<10;j++){
            if(tmpval[j]==0.0)
            {
                dp[i][j][0]=dp[i-1][j][0];
                dp[i][j][1]=dp[i-1][j][1];
            }
            else{
                //cout<<i<< " " <<j<< " "<<tmpval[j]<<endl;
                dp[i][j][0]=tmp[j][0];
                dp[i][j][1]=tmp[j][1];
                lst[j]=i;
                trck[j]=tmpval[j];
            }
        }



    }

    if(lst[m]==0){
        printf("-1\n");
        return 0;
    }

    prn(lst[m],m);

    cout<<vec.size()<<endl;

    for(i=0;i<vec.size();i++){
        printf("%lld ",ara[vec[i]]);
    }

    printf("\n");



    return 0;
}

