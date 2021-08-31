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

const ll sz = 1e5 + 10;
ll pre[sz], a[sz], b[sz];
ll tr[4*sz][2];

void build(ll lo, ll hi, ll node)
{
    if(lo == hi) {
        tr[node][0] = tr[node][1] = pre[lo];
        return;
    }

    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    build(lo, mid, lft);
    build(mid+1, hi, rgt);

    tr[node][0] = min(tr[lft][0], tr[rgt][0]);
    tr[node][1] = max(tr[lft][1], tr[rgt][1]);
}

pll qry(ll lo, ll hi, ll l, ll r, ll node)
{
    if(lo > r || hi < l)
        return mp(inf, -inf);
    if(lo >= l && hi <= r)
        return mp(tr[node][0], tr[node][1]);

    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    pll p1 = qry(lo, mid, l, r, lft);
    pll p2 = qry(mid+1, hi, l, r, rgt);

    return mp(min(p1.ff, p2.ff), max(p1.ss, p2.ss));
}

int main()
{
    ll n, q;
    cin >> n >> q;

    for1(i, n) sl(a[i]);
    for1(i, n) sl(b[i]);

    for1(i, n) pre[i] = a[i]-b[i] + pre[i-1];

    build(1, n, 1);

    while(q--) {
        ll l, r;
        sl(l), sl(r);

        if(pre[r] - pre[l-1] != 0) {
            pf("-1\n");
            continue;
        }

        pll got = qry(1, n, l, r, 1);

        if(got.ss-pre[l-1] > 0)
            pf("-1\n");
        else
            pf("%lld\n", max(abs(got.ff-pre[l-1]), abs(got.ss-pre[l-1])) );

    }

    return 0;
}

