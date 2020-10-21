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

const ll sz = 1e6 + 10;
ll car[sz], n, m;

struct info {
    ll id, gap;
};

struct cmp1 {
    const bool operator ()(const info &a, const info &b) {
        if(a.gap == b.gap)
            return a.id < b.id;
        return a.gap > b.gap;
    }
};
struct cmp2 {
    const bool operator ()(const info &a, const info &b) {
        return a.id < b.id;
    }
};

set <info, cmp1> lst1;
set <info, cmp2> lst2;

inline ll calc_gap(ll l, ll r)
{
    if(l == 0) return r-1;
    if(r == n+1) return n-l;

    ll d = r-l-1;
    return d/2 + (d & 1);
}

int main()
{
    sl(n), sl(m);

    lst1.insert({0, n}), lst2.insert({0, n});
    lst1.insert({n+1, 0}), lst2.insert({n+1, 0});

    for1(i, m) {
        ll op, c;
        sl(op), sl(c);

        if(op == 1) {

            info got = *lst1.begin();

            if(got.id != 0) car[c] = got.id+got.gap;
            else car[c] = 1;

            pf("%lld\n", car[c]);

            lst1.erase(got), lst2.erase(got);

            ll d = calc_gap(got.id, car[c]);
            lst1.insert({got.id, d}), lst2.insert({got.id, d});

            auto it = lst2.upper_bound(got);
            d = calc_gap(car[c], it->id);

            lst1.insert({car[c], d}), lst2.insert({car[c], d});
        }
        else {
            ll id = car[c];
            info got = *lst2.find({id, 0LL});
            lst1.erase(got), lst2.erase(got);

            auto it = lst2.lower_bound(got);
            info lft = *(--it);

            it = lst2.upper_bound(got);
            ll d = calc_gap(lft.id, it->id);

            lst1.erase(lft), lst2.erase(lft);
            lst1.insert({lft.id, d}), lst2.insert({lft.id, d});
        }
    }

    return 0;
}
