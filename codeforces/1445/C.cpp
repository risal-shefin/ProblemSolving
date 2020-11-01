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

vector <pll> lst;
ll mul, ans, p, q, q2;

void solve(ll pos, ll val)
{
    if(pos == lst.size()) {
        const ll mod = q2;
        if(val % mod != 0) ans = max(ans, val);
        return;
    }

    ll num = 1;
    for(ll i = 0; i <= lst[pos].second; i++) {
        solve(pos+1, val*num);
        num *= lst[pos].first;
    }
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        sl(p), sl(q);
        q2 = q;

        if(p % q != 0) {
            pf("%lld\n", p);
            continue;
        }

        mul = p;

        for(ll i = 2; i * i <= q; i++) {

            if(q % i == 0) {

                while(q%i == 0) {
                    q /= i;
                }

                ll cnt = 0;
                while(mul % i == 0) {
                    mul /= i;
                    cnt++;
                }
                if(cnt != 0) lst.pb(mp(i, cnt));
                //cout << i << " " << lst.back().second << " " << tot << EL;
            }
        }

        if(q > 1 && mul % q == 0) {
            ll cnt = 0;
            while(mul % q == 0) {
                mul /= q;
                cnt++;
            }
            lst.pb(mp(q, cnt));
        }

        ans = mul;

        solve(0, mul);

        pf("%lld\n", ans);

        lst.clear();
    }

    return 0;
}

