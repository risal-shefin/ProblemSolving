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

const ll sz = 3e5 + 10, tsz = 2*sz;
pii tr[4*tsz], lz[4*tsz];
int par[sz], mark[sz];

struct info {
    int i, l, r;
    const bool operator <(const info &rhs) {
        return i < rhs.i;
    }
} ara[sz];

void prop(int node)
{
    int lft=node<<1, rgt=lft|1;

    lz[lft] = lz[rgt] = lz[node];
    tr[lft] = tr[rgt] = lz[node];

    lz[node] = {0, 0};
}

void upd(int lo, int hi, int l, int r, pii p, int node)
{
    if(lo > r || hi < l)
        return;
    if(lo >= l && hi <= r) {
        tr[node] = lz[node] = p;
        return;
    }
    if(lz[node].ff != 0) prop(node);

    int mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    upd(lo, mid, l, r, p, lft);
    upd(mid+1, hi, l, r, p, rgt);

    if(tr[lft].ff > tr[rgt].ff) tr[node] = tr[lft];
    else tr[node] = tr[rgt];
}

pii qry(int lo, int hi, int l, int r, int node)
{
    if(lo > r || hi < l)
        return {0, 0};
    if(lo >= l && hi <= r)
        return tr[node];

    if(lz[node].ff != 0) prop(node);

    int mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    pii p1 = qry(lo, mid, l, r, lft), p2 = qry(mid+1, hi, l, r, rgt);

    if(p1.ff > p2.ff) return p1;
    else return p2;
}

int main()
{
    for0(i, 4*tsz) tr[i] = lz[i] = {0, 0};

    ll n, m;
    cin >> n >> m;

    vector <int> num;

    for1(i, m) {
        si(ara[i].i), si(ara[i].l), si(ara[i].r);
        num.pb(ara[i].l), num.pb(ara[i].r);
    }
    sort(ara+1, ara+m+1);

    sort(all(num));
    num.erase(unique(all(num)), num.end());

    ll  mxl = -1, last;

    for1(i, m) {
        ll stop = i, mx = -1, mxr = 0;
        //dbg(i);

        for(ll j = i; j <= m; j++) {
            if(ara[j].i != ara[i].i)
                break;

            stop = j;

            auto [x, l, r] = ara[j];

            l = upper_bound(all(num), l) - num.begin();
            r = upper_bound(all(num), r) - num.begin();
            //dbg(mp(l, r));

            pii got = qry(1, num.size(), l, r, 1);
            if(got.ff > mx) mx = got.ff, mxr = got.ss;

            //dbg(got.ff);
        }

        par[ ara[i].i ] = mxr;
        //dbg(mp(ara[i].i, mxr));

        for(ll j = i; j <= stop; j++) {
            auto [x, l, r] = ara[j];

            l = upper_bound(all(num), l) - num.begin();
            r = upper_bound(all(num), r) - num.begin();
            //cerr << j << "  " << l << " " << r << endl;

            upd(1, num.size(), l, r, {mx+1, x}, 1);
        }

        if(mx+1 > mxl) mxl = mx+1, last = ara[i].i;

        i = stop;
    }
//    for1(i, n) dbg(par[i]);
//    dbg(last);
    //dbg(mxl);

    int cur = last;
    while(cur != 0) {
        mark[cur] = 1;
        cur = par[cur];
    }

    vector <int> ans;
    for1(i, n) {
        if(!mark[i]) ans.pb(i);
    }

    cout << ans.size() << EL;
    for(int &x : ans) pf("%d ", x);
    if(ans.size() != 0) pn;

    return 0;
}

