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
vector <int> g[sz], pos[sz], lst;
vector <bool> valid[sz];
ll valCnt[sz], tim, start[sz], stop[sz], ara[sz];
bool subRoot[sz], parRoot[sz];

void timdfs(ll u, ll p)
{
    start[u] = ++tim;

    for(int &v : g[u]) {
        if(v == p)
            continue;

        timdfs(v, u);
    }

    stop[u] = tim;
}

void dfs(ll u, ll p)
{
    subRoot[u] = 1;
    ll num = ara[u];

    for(ll i = 0; i < g[u].size(); i++) {

        ll v = g[u][i];

        if(v == p)
            continue;

        dfs(v, u);

        if(!subRoot[v]) {
            subRoot[u] = 0;
            continue;
        }

        ll p = lower_bound(all(pos[num]), start[v]) - pos[num].begin();

        if(p == pos[num].size() || pos[num][p] > stop[v])
            valid[u][i] = 1, valCnt[u]++;
        else
            subRoot[u] = 0;
    }
}

void pardfs(ll u, ll p)
{
    ll child = g[u].size();
    if(u != 1) child--;

    for(ll i = 0; i < g[u].size(); i++) {

        ll v = g[u][i];

        if(v == p)
            continue;

        ll valch = valCnt[u], num = ara[v];
        if(valid[u][i]) valch--;

        //cout << u << " || " << valch << " " << child << endl;
        if(parRoot[u] && valch == child-1 && pos[num][0] >= start[v] && pos[num].back() <= stop[v])
            parRoot[v] = 1;

        pardfs(v, u);
    }
}

int main()
{
    ll n; sl(n);
    for1(i, n) {
        sl(ara[i]);
        lst.pb(ara[i]);
    }
    sort(all(lst));
    lst.erase(unique(all(lst)), lst.end());

    for1(i, n) ara[i] = lower_bound(all(lst), ara[i]) - lst.begin();

    for1(i, n-1) {
        ll u, v;
        sl(u), sl(v);

        g[u].pb(v);
        g[v].pb(u);

        valid[u].pb(0);
        valid[v].pb(0);
    }

    timdfs(1, -1);

    for1(i, n) pos[ara[i]].pb(start[i]);
    for0(i, n) sort(all(pos[i]));

    dfs(1, -1);

    parRoot[1] = 1;
    pardfs(1, -1);

    ll ans = 0;
    for1(i, n) {
        //cout << i << " " << subRoot[i] << " " << parRoot[i] << endl;
        if(subRoot[i] && parRoot[i]) {
            //cout << i << endl;
            ans++;
        }
    }

    cout << ans << EL;

    return 0;
}
