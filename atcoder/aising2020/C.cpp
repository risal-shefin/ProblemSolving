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
#define inf (1LL << 62)
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

inline int calc(int b, int c)
{
    int mb = b*b - 4*c;
    if(mb < 0) return 0;

    int sqt = sqrtl(mb);
    if(sqt * sqt != mb) return 0;

    int r1 = -b + sqt, r2 = -b - sqt, ret = 0;

    if(r1 % 2 == 0 && r1 / 2 > 0) ret++;
    if(r2 % 2 == 0 && r2 / 2 > 0) ret++;

    return ret;
}

int main()
{
    ll n;
    cin >> n;

    for1(i, n) {

        ll ans = 0;
        for(int x = 1; x*x <= i; x++) {

            int sqx = x*x;

            for(int y = 1; y*y <= i; y++) {
                int tot = sqx + y*y + x*y;
                if(tot > i) break;

                int k = x+y, c = i - tot;

                ans += calc(k, -c);

                //if(calc(k, -c) > 0) cout << x << " " << y << " " << k << endl;
            }
        }

        pf("%lld\n", ans);
    }

    return 0;
}
