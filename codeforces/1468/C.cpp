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

set < ll > st;
set < pair < ll,ll > > stp;

set < ll > :: iterator it;
set < pair < ll,ll > > :: iterator itp;

ll ara[500005];

int main()
{
    ll test,t,i,j,k,a,b,c,x,y,z,n,m;
    //st.insert(19);
    scl(n);
    for(i=1,k=1;i<=n;i++){
        scl(a);
        if(a==1){
            scl(b);
            stp.insert(mp(-b,k));
            st.insert(k);
            k++;
        }
        else if(a==2){
            while(1){
                it = st.begin();
                if(ara[*it]){
                    st.erase(it);
                }
                else{
                    printf("%lld ",*it);
                    ara[*it]=1;
                    st.erase(it);
                    break;
                }

            }

        }
        else{
            while(1){
                itp = stp.begin();
                pair < ll,ll > pr = *itp;
                if(ara[pr.sc]){
                    stp.erase(itp);
                }
                else{
                    printf("%lld ",pr.sc);
                    ara[pr.sc]=1;
                    stp.erase(itp);
                    break;
                }

            }
        }

    }
    printf("\n");
    return 0;
}

