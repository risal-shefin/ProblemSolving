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

const ll sz = 5e5 + 10;
ll ara[sz], mxLen[sz];
int tr[4*sz];
vector <int> nxt[sz];

void upd(ll lo, ll hi, ll idx, ll v, ll node)
{
    if(lo > idx || hi < idx)
        return;
    if(lo == hi) {
        tr[node] = max(tr[node], (int)v);
        return;
    }

    ll mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    upd(lo, mid, idx, v, lft);
    upd(mid+1, hi, idx, v, rgt);

    tr[node] = max(tr[lft], tr[rgt]);
}

ll qry(ll lo, ll hi, ll l, ll r, ll node)
{
    if(lo > r || hi < l)
        return 0;
    if(lo >= l && hi <= r)
        return tr[node];

    ll mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    return max(qry(lo, mid, l, r, lft),
              qry(mid+1, hi, l, r, rgt));
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n; sl(n);
        for1(i, n) sl(ara[i]), nxt[i].clear(), mxLen[i] = 0;

        for1(i, 4*n) tr[i] = 0;

        stack <int> st;

        for1(i, n) {
            while(!st.empty() && ara[st.top()] <= ara[i])
                st.pop();

            if(!st.empty())
                nxt[st.top()].pb(i);

            st.push(i);
        }

        ll ans = 0;
        for1(i, n) {
            ll q = qry(1, n, 1, ara[i], 1);
            ans = max(ans, q+1);

            for(int &idx : nxt[i]) {
                ll len = qry(1, n, 1, ara[idx], 1);
                ans = max(ans, len+2);

                mxLen[idx] = max(mxLen[idx], len+2);
            }

            mxLen[i] = max(mxLen[i], q+1);
            //cout << i << " || " << mxLen[i] << " " << q << EL;
            upd(1, n, ara[i], mxLen[i], 1);
        }

        pf("%lld\n", ans);
    }

    return 0;
}
