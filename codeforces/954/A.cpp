    #include<bits/stdc++.h>

    #define ll long long

    using namespace std;

    int main()
    {
        ll test;
        cin >> test;
        char ara[110];
        scanf("%s",ara);
        ll c=0;
        for(ll i = 0; i < test; i++)
        {
            if(ara[i]=='U'&&ara[i+1]=='R')
                {
                    ara[i]='D';
                    ara[i+1]='0';
                    c++;
                }
            else if(ara[i]=='R'&&ara[i+1]=='U')
                {

                    ara[i]='D';
                    ara[i+1]='0';
                    c++;
                }
            else if(ara[i]=='U' || ara[i]=='R')
                c++;
        }
        cout<<c<<endl;
    }
