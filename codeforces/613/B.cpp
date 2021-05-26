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

const ll sz = 1e5 + 10;
ll csum[sz], val[sz];

struct info {
    ll val, id;
    const bool operator <(const info &rhs) {
        return val > rhs.val;
    }
} ara[sz];

int main()
{
    ll n, a, cf, cm, m;
    cin >> n >> a >> cf >> cm >> m;

    for1(i, n) sl(ara[i].val), ara[i].id = i;
    sort(ara+1, ara+n+1);

    for1(i, n) csum[i] = csum[i-1] + ara[i].val;

    ll ptr = 1, ans = -inf, idx, idx2, mn;

    for(ll i = 0; i <= n; i++) {
        ll cst = i*a - csum[i];
        if(cst > m) break;

        ll rest = m-cst;

        while(ptr <= i) ptr++;

        while(ptr <= n && ara[ptr].val*(n-ptr+1) - (csum[n]-csum[ptr-1]) > rest)
            ptr++;

        ll len = n-ptr+1;
        cst += ara[ptr].val*len - (csum[n]-csum[ptr-1]);
        rest = m-cst;

        ll mnval;
        if(ptr <= n) mnval = min(a, ara[ptr].val + rest/len);
        else mnval = a;

        ll score = i*cf + mnval*cm;
        if(score > ans)
            ans = score, idx = i, idx2 = ptr, mn = mnval;
    }

    for1(i, idx) val[ara[i].id] = a;

    for(ll i = idx+1; i < idx2; i++) val[ ara[i].id ] = ara[i].val;

    for(ll i = idx2; i <= n; i++) val[ ara[i].id ] = mn;

    cout << ans << EL;
    for1(i, n) pf("%lld ", val[i]);
    pn;

    return 0;
}

// k*len <= rest
// k <= rest/len
