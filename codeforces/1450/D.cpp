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

const ll sz = 3e5 + 10;
ll ans[sz], ara[sz], lft[sz], cnt[sz], exist;
vector <int> erased[sz];
set <int> check;

inline bool validPerm(ll n)
{
    if(check.size() == n && exist == n && *check.rbegin() == n)
        return 1;
    else
        return 0;
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n; sl(n);

        for1(i, n) {
            sl(ara[i]);

            ans[i] = cnt[i] = 0;
        }

        stack <pii> st;

        for1(i, n) {

            while(!st.empty() && st.top().first > ara[i])
                st.pop();

            lft[i] = 1;

            if(!st.empty()) lft[i] = st.top().second + 1;

            st.push(mp(ara[i], i));
        }

        while(!st.empty()) st.pop();

        rep1(i, n) {

            while(!st.empty() && st.top().first >= ara[i])
                st.pop();

            ll rgt = n;
            if(!st.empty()) rgt = st.top().second - 1;

            st.push(mp(ara[i], i));

            ll len = rgt - lft[i] + 1;

            check.insert(ara[i]);
            cnt[ ara[i] ]++;

            erased[len+1].pb(ara[i]);
        }
        exist = n;

        for1(i, n) {
            for(int &val : erased[i]) {

                cnt[val]--, exist--;
                if(cnt[val] == 0) check.erase(val);
            }

            ll len = n-i+1;

            if(validPerm(len)) ans[i] = 1;
        }

        for1(i, n) pf("%lld", ans[i]);
        pn;

        for(ll i = 1; i <= n+1; i++)
            erased[i].clear();

        check.clear();
    }

    return 0;
}

