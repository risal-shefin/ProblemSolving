 // Lights will guide you home

#include <bits/stdc++.h>

#define slld(longvalue) scanf("%lld", &longvalue)

#define ll long long
#define pll pair < long long, long long >

#define fastio ios_base:: sync_with_stdio(false); cin.tie(0); cout.tie(0)

#define bug(x) printf("BUG %lld\n", x)

#define mxlld LLONG_MAX
#define mnlld -LLONG_MAX

using namespace std;

bool check(ll n, ll pos)
{
	return n & (1LL << pos);
}

ll Set(ll n, ll pos)
{
	return n = n | (1LL << pos);
}

vector < ll > vec, tovec, svec;

bool sorted()
{
    return tovec == svec;
}

void op1()
{
    for(ll i = 0; i < tovec.size(); i += 2)
    {
        swap(tovec[i], tovec[i + 1]);
    }

    return;
}

void op2()
{
    for(ll i = 0; i < tovec.size() / 2; i++)
    {
        swap(tovec[i], tovec[i + tovec.size() / 2]);
    }

    return;
}


int main()
{
    ll i, j, k, l, m, n, r, q;
    ll testcase;
    ll in, ans;

//    freopen("input.txt", "r", stdin);

//    freopen("output.txt", "w", stdout);

    while(cin >> n)
    {
        vec.resize(n + n);

        for(auto &it: vec) cin >> it;

        tovec = vec;
        svec = vec;

        sort(svec.begin(), svec.end());

        ans = 10000;
        ll cnt = 0;

        for(ll i = 1; i <= 10000; i++)
        {
            if(sorted()) break;

            cnt++;

            if(i & 1) op1();
            else op2();
        }

        ans = min(ans, cnt);

        cnt = 0;
        tovec = vec;

        for(ll i = 1; i <= 10000; i++)
        {
            if(sorted()) break;

            cnt++;

            if(i & 1) op2();
            else op1();
        }

        ans = min(ans, cnt);

        if(ans == 10000) ans = -1;

        cout << ans << "\n";
    }


}


