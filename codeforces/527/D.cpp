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

const ll sz = 2e5 + 10;
ll tr[4*sz];

struct info {
    ll x, w;
    const bool operator <(const info &rhs) {
        return x < rhs.x;
    }
} ara[sz];

void upd(ll lo, ll hi, ll idx, ll v, ll node)
{
    if(lo > idx || hi < idx)
        return;
    if(lo == hi) {
        tr[node] = v;
        return;
    }

    ll mid = lo+hi>>1, lft= node<<1, rgt=lft|1;

    upd(lo, mid, idx, v, lft);
    upd(mid+1, hi, idx, v, rgt);

    tr[node] = max(tr[lft], tr[rgt]);
}

ll query(ll lo, ll hi, ll l, ll r, ll node)
{
    if(lo > r || hi < l)
        return 0;
    if(lo >= l && hi <= r)
        return tr[node];

    ll mid = lo+hi>>1, lft= node<<1, rgt=lft|1;
    return max(query(lo, mid, l, r, lft),
            query(mid+1, hi, l, r, rgt));
}

int main()
{
    ll n; cin>>n;

    vector <ll> lst;

    for1(i, n) {
        sl(ara[i].x), sl(ara[i].w);
        lst.pb(ara[i].x-ara[i].w);
    }
    sort(ara+1, ara+n+1);
    sort(all(lst));
    lst.erase(unique(all(lst)), lst.end());

    ll ans = 0;
    rep1(i, n) {
        ll start = lower_bound(all(lst), ara[i].x+ara[i].w) - lst.begin();
        ll got = query(0, lst.size(), start, lst.size(), 1);

        ans = max(ans, got+1);

        ll pos = lower_bound(all(lst), ara[i].x-ara[i].w) - lst.begin();
        upd(0, lst.size(), pos, got+1, 1);
    }

    cout << ans << EL;

    return 0;
}
