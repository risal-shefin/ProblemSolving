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
#ifdef LOCALXOX
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

const ll sz = 2e5 + 10, tsz = 1e6 + 10;
ll tr[4*tsz], lz[4*tsz], need[tsz];

struct info {
    ll pw, cn;
    const bool operator <(const info &rhs) {
        return pw < rhs.pw;
    }
} a[sz], b[sz];

struct info2 {
    ll d, a, cn;

    const bool operator <(const info2 &rhs) {
        return d < rhs.d;
    }
} mon[sz];

void build(int lo, int hi, int node)
{
    if(lo == hi) {
        tr[node] = -need[lo];
        lz[node] = 0;
        return;
    }

    int mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    build(lo, mid, lft);
    build(mid+1, hi, rgt);

    tr[node] = max(tr[lft], tr[rgt]);
    lz[node] = 0;
}

inline void prop(int node)
{
    int lft = node<<1, rgt = lft|1;

    tr[lft] += lz[node], tr[rgt] += lz[node];
    lz[lft] += lz[node], lz[rgt] += lz[node];

    lz[node] = 0;
}

void upd(int lo, int hi, int l, int r, ll v, int node)
{
    if(lo > r || hi < l)
        return;
    if(lo >= l && hi <= r) {
        tr[node] += v;
        //cerr << lo << " " << hi << " " << tr[node] << endl;
        lz[node] += v;
        return;
    }

    if(lz[node]) prop(node);

    int mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    upd(lo, mid, l, r, v, lft);
    upd(mid+1, hi, l, r, v, rgt);

    tr[node] = max(tr[lft], tr[rgt]);
}

int main()
{
    ll n, m, p;
    cin >> n >> m >> p;

    for1(i, n) sl(a[i].pw), sl(a[i].cn);
    sort(a+1, a+n+1);

    for1(i, m) sl(b[i].pw), sl(b[i].cn);
    sort(b+1, b+m+1);

    for1(i, p) sl(mon[i].d), sl(mon[i].a), sl(mon[i].cn);
    sort(mon+1, mon+p+1);

    ll cur = m, mn = inf;

    rep0(i, tsz) {
        while(cur >= 1 && b[cur].pw > i) {
            mn = min(mn, b[cur].cn);
            cur--;
        }

        need[i] = mn;
    }

    build(0, tsz-1, 1);
    //dbg(tr[1]);

    ll ans = -inf, ptr = 1;

    for1(i, n) {

        while(ptr <= p && mon[ptr].d < a[i].pw) {
            upd(0, tsz-1, mon[ptr].a, tsz-1, mon[ptr].cn, 1);
            ptr++;
        }
        //dbg(tr[1]);

        ans = max(ans, tr[1] - a[i].cn);
    }

    cout << ans << EL;

    return 0;
}
