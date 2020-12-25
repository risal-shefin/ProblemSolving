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

vector < ll > bomb;

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
		ll a, b;

		cin >> n >> m >> a >> b;

		bomb.resize(m);

		for(auto &it: bomb) cin >> it;

		sort(bomb.begin(),bomb.end());

		if(a > b)
		{
			a = n - a + 1;
			b = n - b + 1;
		}

		ll t1 = b - 1;
		ll mxcrack = b - a - 1;

		ans = 0;

		for(ll i = min(m - 1, mxcrack - 1); i >= 0; i--)
		{
			if(bomb[i] < t1)
			{
				t1--;
				ans++;
			}
		}

		cout << ans << "\n";
    }


}


