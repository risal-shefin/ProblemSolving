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

const ll sz = 1e5 + 10;
vector <ll> g[sz];
ll ara[sz], sub[sz], mul[sz], zero;

void sub_dfs(ll u, ll p)
{
    sub[u] += ara[u];

    for(ll &v : g[u]) {
        if(v == p)
            continue;

        sub_dfs(v, u);
        sub[u] += sub[v];
    }
}

void dfs(ll u, ll p)
{
    ll c = g[u].size();
    if(p != -1) c--;
    mul[u] = 1;

    if(c == 0) return;

    for(ll &v : g[u]) {
        if(v == p)
            continue;

        dfs(v, u);
        if(zero) return;

        ll a = mul[u], b = mul[v], g = __gcd(a, b);
        a /= g;

        if(a > sub[u]/b) {
            zero = 1;
            return;
        }

        mul[u] = a*b;
    }

    if(c > sub[u]/mul[u]) zero = 1;
    else mul[u] = c*mul[u];
}

bool isPos(ll u, ll p, ll x)
{
    ll c = g[u].size(), ret = 1;
    if(p != -1) c--;

    if(c == 0) return ara[u] >= x;

    for(ll &v : g[u]) {
        if(v == p)
            continue;

        ret &= isPos(v, u, x/c);
    }
    return ret;
}

int main()
{
    ll n; sl(n);
    for1(i, n) sl(ara[i]);

    for1(i, n-1) {
        ll u, v;
        sl(u), sl(v);

        g[u].pb(v);
        g[v].pb(u);
    }

    sub_dfs(1, -1);
    dfs(1, -1);

    if(zero) {
        pf("%lld\n", sub[1]);
        return 0;
    }

    ll mxm = sub[1]/mul[1];

    ll lo = 0, hi = mxm, ret;
    while(lo <= hi) {
        ll mid = lo+hi>>1;

        if(isPos(1, -1, mul[1]*mid)) {
            ret = mul[1]*mid;
            lo = mid+1;
        }
        else
            hi = mid-1;
    }

    pf("%lld\n", sub[1]-ret);

    return 0;
}
