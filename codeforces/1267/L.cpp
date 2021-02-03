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

ll cnt[100];
char ch[1000005],out[1005][1005];

int main()
{
    ll test,p,q,t,i,j,k,a,b,c,x,y,z,n,m;
    scll(n,m);
    scl(q);
    scs(ch);

    for(i=0;i<n*m;i++){
        cnt[ch[i]-'a']++;
    }
    p=1;
    for(i=0,j=0;i<26 && j<m;)
    {
        if(cnt[i]==0){
            i++;
            continue;
        }
        x=q-p+1;
        if(cnt[i]>=x){

            cnt[i]-=x;
            for(k=p;k<=q;k++){
                out[k][j]=i+'a';
            }
            j++;
        }
        else{
            for(k=p;k<p+cnt[i];k++){
                out[k][j]=i+'a';
            }
            p+=cnt[i];
            cnt[i++]=0;
        }

    }
    for(i=1,k=0;i<=n;i++){
        for(j=0;j<m;j++){
            if(out[i][j]==0){
                while(cnt[k]<=0){
                    k++;
                }
                out[i][j]=k+'a';
                cnt[k]--;
            }
        }
        out[i][j]='\0';
        printf("%s\n",out[i]);
    }




    return 0;
}

