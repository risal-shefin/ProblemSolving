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

const ll sz = 35009;
ll tr[4*sz], lazy[4*sz], dp[sz][109], ara[sz], last[sz], prv[sz];

void build(ll lo, ll hi, ll k, ll node)
{
    if(lo == hi) {
        tr[node] = dp[lo][k];
        lazy[node] = 0;
        return;
    }

    ll mid = lo+hi>>1, lft = node<<1, rgt=lft|1;

    build(lo, mid, k, lft);
    build(mid+1, hi, k, rgt);

    tr[node] = min(tr[lft], tr[rgt]);
    lazy[node] = 0;
}

void prop(ll lo, ll hi, ll node)
{
    ll mid = lo+hi>>1, lft = node<<1, rgt=lft|1;

    tr[lft] += lazy[node], tr[rgt] += lazy[node];
    lazy[lft] += lazy[node], lazy[rgt] += lazy[node];

    lazy[node] = 0;
}

void upd(ll lo, ll hi, ll l, ll r, ll v,  ll node)
{
    if(lo > r || hi < l)
        return;
    if(lo >= l && hi <= r) {
        tr[node] += v;
        lazy[node] += v;
        return;
    }
    if(lazy[node]) prop(lo, hi, node);

    ll mid = lo+hi>>1, lft = node<<1, rgt=lft|1;

    upd(lo, mid, l, r, v, lft);
    upd(mid+1, hi, l, r, v, rgt);

    tr[node] = min(tr[lft], tr[rgt]);
}

ll query(ll lo, ll hi, ll l, ll r, ll node)
{
    if(lo > r || hi < l)
        return inf;
    if(lo >= l && hi <= r)
        return tr[node];

    if(lazy[node]) prop(lo, hi, node);

    ll mid = lo+hi>>1, lft = node<<1, rgt=lft|1;

    return min(query(lo, mid, l, r, lft),
               query(mid+1, hi, l, r, rgt));
}

int main()
{
    ll n, k;
    cin >> n >> k;

    for1(i, n) {
        sl(ara[i]);

        prv[i] = last[ ara[i] ];
        last[ ara[i] ] = i;
    }

    for1(i, n) dp[i][0] = inf;
    for1(i, k) dp[0][i] = inf;
    dp[0][0] = 0;

    build(0, n, 0, 1);

    for1(x, k) {

        for1(i, n) {
            if(prv[i] != 0)
                upd(0, n, 0, prv[i]-1, i-prv[i], 1);

            dp[i][x] = query(0, n, 0, i-1, 1);
        }
        build(0, n, x, 1);
    }

    cout << dp[n][k] << EL;

    return 0;
}
