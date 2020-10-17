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
ll target[sz], vis[sz];
set <int> colLst[3];
vector <int> rowLst;
vector <pii> ans;

int main()
{
    ll n; sl(n);
    for1(i, n) {
        sl(target[i]);

        if(target[i] == 1) colLst[1].insert(i);
        else if(target[i] > 1) colLst[2].insert(i);
    }

    rep1(i, n) rowLst.pb(i);

    ll flag = 1;

    for1(c, n) {
        if(target[c] == 0 || vis[c])
            continue;

        if(rowLst.empty()) {
            flag = -1;
            break;
        }

        if(target[c] == 1) {

            ll r = rowLst.back();
            ans.pb(mp(r, c));

            rowLst.pop_back();
            continue;
        }

        if(target[c] == 2) {

            auto it = colLst[1].upper_bound(c);
            if(it == colLst[1].end()) {
                flag = -1;
                break;
            }

            vis[*it] = 1;
            ll r = rowLst.back();
            ans.pb(mp(r, c)), ans.pb(mp(r, *it));

            rowLst.pop_back(), colLst[1].erase(it);

            continue;
        }

        auto itc = colLst[2].upper_bound(c);
        ll r = rowLst.back(), notOne = 1;

        if(itc == colLst[2].end()) {
            notOne = 0;

            itc = colLst[1].upper_bound(c);
            if(itc == colLst[1].end()) {
                flag = -1;
                break;
            }
        }

        ans.pb(mp(r, c)), ans.pb(mp(r, *itc));
        rowLst.pop_back();

        if(notOne) colLst[2].erase(itc);
        else colLst[1].erase(itc);
    }

    if(flag == -1) {
        cout << -1 << EL;
        return 0;
    }

    cout << ans.size() << EL;
    for(pii &pnt : ans) pf("%d %d\n", pnt.first, pnt.second);

    return 0;
}
