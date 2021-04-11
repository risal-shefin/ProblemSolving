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
#else
#define dbg(x)
#endif
// === Debug macro ends here ===

#define ff first
#define ss second

const ll sz = 2e5 + 10;
ll ara[sz], par[sz], tr[4*sz];

ll findp(ll u)
{
    if(par[u] == u)
        return u;
    return par[u] = findp(par[u]);
}

struct edge {
    ll u, v, w;
    const bool operator <(const edge &b) {
        return w < b.w;
    }
} Edge[4*sz];

void build(ll lo, ll hi, ll node)
{
    if(lo == hi) {
        tr[node] = ara[lo];
        return;
    }

    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    build(lo, mid, lft);
    build(mid+1, hi, rgt);

    tr[node] = __gcd(tr[lft], tr[rgt]);
}

ll query(ll lo, ll hi, ll l, ll r, ll node)
{
    if(lo > r || hi < l)
        return 0;
    if(lo >= l && hi <= r)
        return tr[node];

    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    return __gcd(query(lo, mid, l, r, lft),
                 query(mid+1, hi, l, r, rgt));
}

int main()
{
    fastio;

    ll t;
    cin >> t;

    while(t--) {
        ll n, p, idx = 0;
        cin >> n >> p;

        for1(i, n) {
            cin >> ara[i];

            if(i < n) Edge[++idx] = {i, i+1, p};
        }
        build(1, n, 1);

        ll start = 2;
        for1(i, n) {

            ll g = query(1, n, i, start, 1), stop = i+1;

            for(ll j = start; j <= n && ara[j] >= ara[i]; j++) {
                g = __gcd(g, ara[j]);
                if(g != ara[i])
                    break;

                Edge[++idx] = {i, j, ara[i]};
                stop = j;
            }

            start = max(start, stop+1);
        }

        start = n-1;
        rep1(i, n) {

            ll g = query(1, n, start, i, 1), stop = i-1;

            for(ll j = start; j >= 1 && ara[j] >= ara[i]; j--) {
                g = __gcd(g, ara[j]);
                if(g != ara[i])
                    break;

                Edge[++idx] = {i, j, ara[i]};
                stop = j;
            }

            start = min(start, stop-1);
        }

        sort(Edge+1, Edge+idx+1);

        for1(i, n) par[i] = i;

        ll ans = 0;

        for1(i, idx) {
            ll u = Edge[i].u, v = Edge[i].v, w = Edge[i].w;
            ll pu = findp(u), pv = findp(v);
            if(pu == pv)
                continue;

            ans += w;
            par[pv] = pu;
        }

        cout << ans << EL;
    }

    return 0;
}

