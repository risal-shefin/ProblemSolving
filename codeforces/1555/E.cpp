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

const ll sz = 3e5 + 10, tsz = 1e6 + 10;
int tr[4*tsz], lazy[4*tsz];

void prop(int node)
{
    int lft=node<<1, rgt=lft|1;

    tr[lft] += lazy[node], tr[rgt] += lazy[node];
    lazy[lft] += lazy[node], lazy[rgt] += lazy[node];

    lazy[node] = 0;
}

void upd(int lo, int hi, int l, int r, int x, int node)
{
    if(lo > r || hi < l)
        return;
    if(lo >= l && hi <= r) {
        tr[node] += x, lazy[node] += x;
        return;
    }
    if(lazy[node]) prop(node);

    int mid=lo+hi>>1, lft=node<<1, rgt=lft|1;

    upd(lo,mid, l, r, x,lft);
    upd(mid+1,hi,l,r,x,rgt);

    tr[node] = min(tr[lft], tr[rgt]);
}

struct info {
    int l, r, w;
    const bool operator <(const info &rhs) {
        return w < rhs.w;
    }
} ara[sz];

int main()
{
    ll n, m;
    cin >> n >> m;

    for1(i, n) {
        sl(ara[i].l), sl(ara[i].r), sl(ara[i].w);
        ara[i].r--;
    }
    sort(ara+1, ara+n+1);

    ll ans = inf, ptr = 0;

    for1(i, n) {
        while(tr[1] == 0 && ptr+1 <= n) {
            ++ptr;
            upd(1, m-1, ara[ptr].l, ara[ptr].r, 1, 1);
        }

        if(tr[1] == 0) break;

        //dbg(mp(i, ptr));
        ans = min(ans, (ll)ara[ptr].w - ara[i].w);

        upd(1, m-1, ara[i].l, ara[i].r, -1, 1);
    }

    cout << ans << EL;

    return 0;
}
