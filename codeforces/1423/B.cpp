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

const ll sz = 1e5 + 10, MAX_N = 1e4 + 10;

struct Edge {
    ll u, v, c;
} ed[sz];
const bool operator <(const Edge &a, const Edge &b)
{
    return a.c < b.c;
}

set <int> airport, factory;

int main()
{
    ll n, m;
    cin >> n >> m;

    for1(i, m) {
        sl(ed[i].u), sl(ed[i].v), sl(ed[i].c);
    }
    sort(ed+1, ed+m+1);

    ll ans = -1;

    for1(i, m) {
        airport.insert(ed[i].u);
        factory.insert(ed[i].v);

        if(airport.size() == n && factory.size() == n) {
            ans = ed[i].c;
            break;
        }
    }

    cout << ans << EL;

    return 0;
}
