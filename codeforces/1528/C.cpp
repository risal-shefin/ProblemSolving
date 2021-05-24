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

// === Debug macro starts here ===
#ifndef ONLINE_JUDGE
#define DEBUG
#define SYS_COL system("COLOR")
#endif

int recur_depth = 0;
#ifdef DEBUG
#define dbg(x) {++recur_depth; auto x_=x; --recur_depth; SYS_COL; \
                cerr<<string(recur_depth, '\t')<<"\e[91m"<<__func__<<":" \
                <<__LINE__<<"\t"<<#x<<" = "<<x_<<"\e[39m"<<endl;}

template<typename Ostream, typename Cont>
typename enable_if<is_same<Ostream,ostream>::value,
            Ostream&>::type operator<<(Ostream& os,  const Cont& v) {
	os<<"[";
	for(auto& x:v){os<<x<<", ";}
	return os<<"]";
}
template<typename Ostream, typename ...Ts>
Ostream& operator<<(Ostream& os,  const pair<Ts...>& p){
	return os<<"{"<<p.first<<", "<<p.second<<"}";
}
#else
#define dbg(x)
#endif
// === Debug macro ends here ===

#define ff first
#define ss second

const ll sz = 3e5 + 10;
vector <ll> g[sz], g2[sz];
ll start[sz], stop[sz], tim, ans, tr[4*sz], lazy[4*sz], n;

ll BITree[sz];

ll getSum(ll index)
{
    ll sum = 0;
    while (index>0)
    {
        sum += BITree[index];
        index -= index & (-index);
    }
    return sum;
}

void updateBIT(ll n, ll index, ll val)
{
    while (index <= n)
    {
       BITree[index] += val;
       index += index & (-index);
    }
}

inline ll bquery(ll l, ll r)
{
    return getSum(r) - getSum(l-1);
}

void prop(ll lo, ll hi, ll node)
{
    ll mid = lo+hi>>1, lft=node<<1, rgt=lft|1;
    tr[lft] = tr[rgt] = lazy[lft] = lazy[rgt] = lazy[node];
    lazy[node] = inf;
}

void upd(ll lo, ll hi, ll l, ll r, ll v, ll node)
{
    if(lo > r || hi < l)
        return;
    if(lo >= l && hi <= r) {
        tr[node] = lazy[node] = v;
        return;
    }

    if(lazy[node] != inf) prop(lo, hi, node);

    ll mid = lo+hi>>1, lft=node<<1, rgt=lft|1;
    upd(lo, mid, l, r, v, lft);
    upd(mid+1, hi, l, r, v, rgt);
}

ll query(ll lo, ll hi, ll idx, ll node)
{
    if(lo > idx || hi < idx)
        return 0;
    if(lo == hi)
        return tr[node];

    if(lazy[node] != inf) prop(lo, hi, node);

    ll mid = lo+hi>>1, lft=node<<1, rgt=lft|1;
    return max(query(lo, mid, idx, lft),
               query(mid+1, hi, idx, rgt));
}

void dfs(ll u)
{
    start[u] = ++tim;

    for(ll &v : g2[u])
        dfs(v);

    stop[u] = tim;
}

void ans_dfs(ll u)
{
    ll sub = bquery(start[u], stop[u]);
    ll ancestor = query(1, n, start[u], 1);

    if(sub == 0) {
        if(ancestor != 0) {
            upd(1, n, start[ancestor], stop[ancestor], 0, 1);
            updateBIT(n, start[ancestor], -1);
        }

        updateBIT(n, start[u], 1);
        upd(1, n, start[u], stop[u], u, 1);

        ans = max(ans, getSum(n));
        //dbg(ancestor);
    }

    for(ll &v : g[u])
        ans_dfs(v);

    if(sub == 0) {
        upd(1, n, start[u], stop[u], 0, 1);
        updateBIT(n, start[u], -1);

        if(ancestor != 0) {
            upd(1, n, start[ancestor], stop[ancestor], ancestor, 1);
            updateBIT(n, start[ancestor], 1);
        }
    }
}

void clr(ll n)
{
    for1(i, n) {
        g[i].clear();
        g2[i].clear();
        BITree[i] = 0;
    }
    for(ll i = 0; i <= 4*n; i++) {
        tr[i] = 0, lazy[i] = inf;
    }
    tim = ans = 0;
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        sl(n);
        clr(n);

        for(ll i = 2; i <= n; i++) {
            ll p; sl(p);
            g[p].pb(i);
        }

        for(ll i = 2; i <= n; i++) {
            ll p; sl(p);
            g2[p].pb(i);
        }

        dfs(1);
        ans_dfs(1);

        pf("%lld\n", ans);
        //dbg(ans);
    }

    return 0;
}

