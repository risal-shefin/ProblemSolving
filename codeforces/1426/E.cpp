// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define dd double
#define ld long double
#define sl(n) scanf("%lld", &n)
#define si(n) scanf("%d", &n)
#define sd(n) scanf("%lf", &n)
#define pll pair <ll, ll>
#define pii pair <int, int>
#define mp make_pair
#define pb push_back
#define all(v) v.begin(), v.end()
#define inf (1LL << 61)
#define loop(i, start, stop, inc) for(ll i = start; i <= stop; i += inc)
#define for1(i, stop) for(ll i = 1; i <= stop; ++i)
#define for0(i, stop) for(ll i = 0; i < stop; ++i)
#define rep1(i, start) for(ll i = start; i >= 1; --i)
#define rep0(i, start) for(ll i = (start-1); i >= 0; --i)
#define ms(n, i) memset(n, i, sizeof(n))
#define casep(n) printf("Case %lld:", ++n)
#define pn printf("\n")
#define pf printf
#define EL '\n'
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

ll a[3], b[3];

ll solve(ll pos)
{
    if(pos == 3) return 0;

    ll nxt = pos+1;
    if(nxt == 3) nxt = 0;

    ll mn1 = min(b[pos], a[nxt]);
    b[pos] -= mn1, a[nxt] -= mn1;

    ll mn2 = min(b[pos], a[pos]);
    b[pos] -= mn2, a[pos] -= mn2;

    ll ret = mn1 + mn2 + solve(pos+1);

    b[pos] += mn1, a[nxt] += mn1;
    b[pos] += mn2, a[pos] += mn2;


    mn2 = min(b[pos], a[pos]);
    b[pos] -= mn2, a[pos] -= mn2;

    mn1 = min(b[pos], a[nxt]);
    b[pos] -= mn1, a[nxt] -= mn1;

    ll ret2 = mn1 + mn2 + solve(pos+1);

    b[pos] += mn1, a[nxt] += mn1;
    b[pos] += mn2, a[pos] += mn2;

    return max(ret, ret2);
}

int main()
{
    ll n;
    cin >> n;
    for0(i, 3) sl(a[i]);
    for0(i, 3) sl(b[i]);

    ll ptr = 1, wina = 0;

    for0(i, 3) {
        wina += min(a[i], b[ptr]);

        ptr++;
        if(ptr == 3) ptr = 0;
    }

    ll totb = solve(0);

    cout << n-totb << " " << wina << EL;

    return 0;
}
