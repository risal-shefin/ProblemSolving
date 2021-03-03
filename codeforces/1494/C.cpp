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

const ll sz = 2e5 + 10;
ll done[sz];

ll solve(vector<int> a, vector <int> b)
{
    if(a.empty() || b.empty())
        return 0;

    done[b.size()] = 0;
    for(ll i = b.size()-1; i >= 0; i--) {

        ll pos = lower_bound(all(a), b[i]) - a.begin();

        if(pos != a.size() && a[pos] == b[i])
            done[i] = 1;
        else
            done[i] = 0;

        done[i] += done[i+1];
    }

    ll ret = 0;
    for(ll i = 0; i < b.size(); i++) {

        ll lo = 0, hi = a.size()-1, got = -inf;
        while(lo <= hi) {
            ll mid = lo+hi>>1;

            if(b[i]+mid >= a[mid]) {
                got = mid;
                lo = mid+1;
            }
            else
                hi = mid-1;
        }
        if(got == -inf)
            continue;

        ll pos = upper_bound(all(b), b[i]+got) - b.begin();

        ll cnt = (pos-i) + done[pos];

        ret = max(ret, cnt);
    }

    return ret;
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n, m;
        sl(n), sl(m);

        vector <int> nega, negb, posa, posb;

        for1(i, n) {
            ll inp; sl(inp);

            if(inp < 0) nega.pb(-inp);
            else posa.pb(inp);
        }
        reverse(all(nega));

        for1(i, m) {
            ll inp; sl(inp);

            if(inp < 0) negb.pb(-inp);
            else posb.pb(inp);
        }
        reverse(all(negb));

        pf("%lld\n", solve(nega, negb) + solve(posa, posb));
    }

    return 0;
}
