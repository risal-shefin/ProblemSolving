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
struct info {
    ll cnt, id;
} ara[sz];
set <info> lst;

const bool operator <(const info &a, const info &b)
{
    if(a.cnt == b.cnt)
        return a.id < b.id;

    return a.cnt < b.cnt;
}

int main()
{
    ll n, s, sum = 0;
    cin >> n >> s;

    for1(i, n) {
        sl(ara[i].cnt);
        ara[i].id = i;
        sum += ara[i].cnt;

        if(ara[i].cnt != 0) lst.insert(ara[i]);
    }

    if(sum & 1) {
        cout << "No" << EL;
        return 0;
    }

    sort(ara+1, ara+n+1);

    vector <pii> ans;
    ans.reserve(s);
    bool ok = 1;

    while(!lst.empty()) {
        if(lst.size() == 1) {
            ok = 0;
            break;
        }

        auto it1 = --lst.end();
        info u = *it1;
        lst.erase(u);

        vector <info> LOL;

        for1(i, u.cnt) {
            if(lst.empty()) {
                ok = 0;
                break;
            }
            auto it2 = --lst.end();
            info v = *it2;
            lst.erase(v);

            ans.pb(mp(u.id, v.id));

            v.cnt--;
            if(v.cnt != 0) LOL.pb(v);
        }

        if(!ok) break;

        for(info &x : LOL) lst.insert(x);
    }

    if(!ok) pf("No\n");
    else {
        pf("Yes\n");
        pf("%lld\n", (ll)ans.size());

        for(pii &p: ans)
            pf("%d %d\n", p.first, p.second);
    }

    return 0;
}
