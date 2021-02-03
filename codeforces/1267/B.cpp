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
vector < pll > v;
ll solve()
{
	ll bam = 0;
	ll dan = str.size() - 1;
	v.clear();

	char cc = 'x';
	ll cnt = 0;

	for(auto it: str)
	{
		if(it == cc) cnt++;
		else
		{
			if(cnt) v.push_back({cnt, cc});

			cc = it;
			cnt = 1;
		}
	}

	v.push_back({cnt, cc});

	for(ll i = 0, j = v.size() - 1; i <= j; i++, j--)
	{
		if(i == j)
		{
			if(v[i].first < 2) return 0;

			return v[i].first + 1;
		}

		if(v[i].second != v[j].second) return 0;

		if(v[i].first + v[j].first < 3) return 0;
	}

	assert(0);
}

int main()
{
    ll i, j, k, l, m, n, o, r, q;
    ll testcase;
    ll input, flag, tag, ans;

//    freopen("input.txt", "r", stdin);

//    freopen("output.txt", "w", stdout);

    while(cin >> str)
    {
		ans = solve();

		cout << ans << "\n";
    }


}


