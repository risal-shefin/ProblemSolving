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

const ll sz = 1e5 + 10;
bool chk[sz], del[sz], used[sz], small;
vector <ll> prime;
ll tot, n;

inline ll query(char typ, ll num)
{
    cout << typ << " " << num << endl;
    ll x; cin >> x;
    return x;
}

inline bool check_prime(ll p)
{
    ll cnt = 0;
    for(ll j = p; j <= n; j += p) {
        if(del[j])
            continue;

        del[j] = 1, cnt++;
    }
    tot -= cnt;

    ll got = query('B', p);
    return got != cnt;
}

inline ll calc_factor(ll p)
{
    ll v = 1;
    while(v*p <= n && query('A', v*p) != 0)
        v *= p;
    return v;
}

int main()
{
    fastio;

    cin >> n;

    for(ll i = 2; i <= n; i++) {
        if(!chk[i]) {
            for(ll j = i*i; j <= n; j += i)
                chk[j] = 1;

            prime.pb(i);
        }
    }

    ll ans = 1, sqt = sqrtl(prime.size());
    tot = n;

    for(ll i = 0; i < prime.size(); i++) {

        ll p = prime[i];

        if(check_prime(p)) ans *= calc_factor(p);

        if((i+1 != prime.size() && i % sqt != sqt-1) || small)
            continue;

        ll got = query('A', 1);
        if(got != tot) {

            tot = got;
            ll b = i / sqt;

            for(ll j = b*sqt; j <= i && !small; j++) {

                p = prime[j];

                if(check_prime(p)) ans *= calc_factor(p), small = 1;
            }
        }
    }

    cout << "C " << ans << endl;

    return 0;
}
