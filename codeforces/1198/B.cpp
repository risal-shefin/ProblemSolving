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

// === DEBUG MACRO STARTS HERE === //
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
// === DEBUG MACRO ENDS HERE === //

#define ff first
#define ss second

const ll sz = 2e5 + 10;
ll tr[4*sz], lazy[4*sz], ara[sz];

void build(ll lo, ll hi, ll node)
{
    if(lo == hi) {
        tr[node] = ara[lo];
        return;
    }

    ll mid = lo+hi>>1, lft = node<<1, rgt=lft|1;
    build(lo, mid, lft);
    build(mid+1, hi, rgt);

    tr[node] = max(tr[lft], tr[rgt]);
}

void prop(ll lo, ll hi, ll node)
{
    ll mid = lo+hi>>1, lft = node<<1, rgt=lft|1;

    lazy[lft] = max(lazy[lft], lazy[node]);
    lazy[rgt] = max(lazy[rgt], lazy[node]);

    tr[lft] = max(tr[lft], lazy[node]);
    tr[rgt] = max(tr[rgt], lazy[node]);

    lazy[node] = 0;
}

void upd(ll lo, ll hi, ll l, ll r, ll x, bool a, ll node)
{
    if(lo > r || hi < l)
        return;
    if(lo >= l && hi <= r) {
        if(a) {
            tr[node] = x;
            return;
        }
        tr[node] = max(tr[node], x);
        lazy[node] = max(lazy[node], x);
        return;
    }
    if(lazy[node]) prop(lo, hi, node);

    ll mid = lo+hi>>1, lft = node<<1, rgt=lft|1;
    upd(lo, mid, l, r, x, a, lft);
    upd(mid+1, hi, l, r, x, a, rgt);

    tr[node] = max(tr[lft], tr[rgt]);
}

ll qry(ll lo, ll hi, ll idx, ll node)
{
    if(lo > idx || hi < idx)
        return 0;
    if(lo == hi)
        return tr[node];

    if(lazy[node]) prop(lo, hi, node);

    ll mid = lo+hi>>1, lft = node<<1, rgt=lft|1;
    return max(qry(lo, mid, idx, lft),
               qry(mid+1, hi, idx, rgt));
}

int main()
{
    ll n; sl(n);
    for1(i, n) sl(ara[i]);
    build(1, n, 1);

    ll q; sl(q);
    while(q--) {
        ll op; sl(op);

        if(op == 1) {
            ll p, x;
            sl(p), sl(x);
            upd(1, n, p, p, x, 1, 1);
        }
        else {
            ll x; sl(x);
            upd(1, n, 1, n, x, 0, 1);
        }
    }

    for1(i, n) pf("%lld ", qry(1, n, i, 1));
    pn;

    return 0;
}
