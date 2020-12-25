// God put a smile upon your face <3

#include <bits/stdc++.h>

#define slld(longvalue) scanf("%lld", &longvalue)

#define ll long long
#define ull unsigned long long
#define pll pair < long long, long long >

#define fastio ios_base:: sync_with_stdio(false); cin.tie(0); cout.tie(0)

#define pb push_back

#define bug printf("BUG\n")

#define mxlld LLONG_MAX
#define mnlld -LLONG_MAX

#define mxd 2e8
#define mnd -2e8

#define pi 3.14159265359

using namespace std;

bool check(ll n, ll pos)
{
    return n & (1LL << pos);
}

ll Set(ll n, ll pos)
{
    return n = n | (1LL << pos);
}

string str;

pll solve(ll bx, ll by)
{
    ll x = 0, y = 0;

    for(auto it: str)
    {
		ll px = x;
		ll py = y;

        if(it == 'U') y++;
        if(it == 'R') x++;
        if(it == 'D') y--;
        if(it == 'L') x--;

        if(x == bx && y == by)
        {
			x = px;
			y = py;
        }
    }

    if(x == 0 && y == 0) return {bx,by};

    return {0,0};
}

int main()
{
    ll i, j, k, l, m, n, o, r, q;
    ll testcase;
    ll input, flag, tag, ans;

//    freopen("input.txt", "r", stdin);

//    freopen("output.txt", "w", stdout);

    slld(testcase);

    for(ll cs = 1; cs <= testcase; cs++)
    {
        cin >> str;

        ll x = 0, y = 0;
        pll ans = {0,0};


        for(auto it: str)
        {
            if(it == 'U') y++;
            if(it == 'R') x++;
            if(it == 'D') y--;
            if(it == 'L') x--;

            if(x != 0 || y != 0)
            {
                ans = solve(x,y);

                if(ans.first != 0 || ans.second != 0) break;
            }
        }

        cout << ans.first << " " << ans.second << "\n";

    }


}


