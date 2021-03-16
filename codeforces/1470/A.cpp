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
#define dbg(x) {++recur_depth; auto x_=x; --recur_depth; SYS_COL; cerr<<string(recur_depth, '\t')<<"\e[91m"<<__func__<<":"<<__LINE__<<"\t"<<#x<<" = "<<x_<<"\e[39m"<<endl;}
#else
#define dbg(x)
#endif
template<typename Ostream, typename Cont>
typename enable_if<is_same<Ostream,ostream>::value, Ostream&>::type operator<<(Ostream& os,  const Cont& v){
	os<<"[";
	for(auto& x:v){os<<x<<", ";}
	return os<<"]";
}
template<typename Ostream, typename ...Ts>
Ostream& operator<<(Ostream& os,  const pair<Ts...>& p){
	return os<<"{"<<p.first<<", "<<p.second<<"}";
}

// === Debug macro ends here ===

#define ff first
#define ss second

const ll sz = 3e5 + 10;
pll tr[4*sz];
ll ara[sz], val[sz];

void build(ll lo, ll hi, ll node)
{
    if(lo == hi) {
        tr[node] = {ara[lo], lo};
        return;
    }

    ll mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    build(lo, mid, lft);
    build(mid+1, hi, rgt);

    tr[node] = min(tr[lft], tr[rgt]);
}

void upd(ll lo, ll hi, ll idx, ll v, ll node)
{
    if(lo > idx || hi < idx)
        return;
    if(lo == hi) {
        tr[node] = {v, lo};
        return;
    }

    ll mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    upd(lo, mid, idx, v, lft);
    upd(mid+1, hi, idx, v, rgt);

    tr[node] = min(tr[lft], tr[rgt]);
}

pll query(ll lo, ll hi, ll l, ll r, ll node)
{
    if(lo > r || hi < l)
        return {inf, inf};
    if(lo >= l && hi <= r)
        return tr[node];

    ll mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    return min(query(lo,mid, l, r, lft),
               query(mid+1,hi, l, r, rgt));
}

struct cmp {
    const bool operator()(const int &a, const int &b) {
        return ara[a] > ara[b];
    }
};
multiset <int, cmp> lst;

int main()
{
    ll t;
    cin >> t;
    while(t--) {
        ll n, m;
        sl(n), sl(m);

        for1(i, n) sl(val[i]);
        for1(i, m) sl(ara[i]);

        lst.clear();
        for1(i, n) {
            lst.insert(val[i]);
        }
        build(1, m, 1);

        ll ans = 0;
        while(!lst.empty()) {
            auto k = *lst.begin();
            lst.erase(lst.find(k));

            pll got = query(1, m, 1, k, 1);
            if(got.ff < ara[k]) {
                ans += got.ff;
                upd(1, m, got.ss, inf, 1);
            }
            else
                ans += ara[k];

            //cout << k << " " << got.ff << EL;
        }

        pf("%lld\n", ans);
    }

    return 0;
}
