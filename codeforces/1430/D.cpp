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
char s[sz];

struct info {
    int start, len;
};

struct cmp1 {
    const bool operator ()(const info &a, const info &b)
    {
        ll state1 = a.len >= 2, state2 = b.len >= 2;

        if(state1 == state2)
            return a.start < b.start;

        return state1 > state2;
    }
};

struct cmp2 {
    const bool operator ()(const info &a, const info &b) {
        return a.start < b.start;
    }
};

set <info, cmp1> lst1;
set <info, cmp2> lst2;

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n; sl(n);
        scanf("%s", s+1);

        for1(i, n) {

            ll start = i, stop = i;

            for(ll j = i; j <= n; j++) {
                if(s[j] != s[start])
                    break;
                stop = j;
            }

            info now = {i, stop-start+1};
            lst1.insert(now), lst2.insert(now);

            i = stop;
        }

        ll step = 0;

        while(!lst2.empty()) {

            step++;

            info now = *lst2.begin();

            lst1.erase(now), lst2.erase(now);

            if(now.len > 1 || lst2.empty())
                continue;

            info now2 = *lst1.begin();

            lst1.erase(now2), lst2.erase(now2);

            now2.len--;
            if(now2.len != 0)
                lst1.insert(now2), lst2.insert(now2);
        }

        pf("%lld\n", step);
    }

    return 0;
}
