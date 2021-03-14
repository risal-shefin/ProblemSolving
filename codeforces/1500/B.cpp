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
#define ff first
#define ss second

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


const ll sz = 1e6 + 10;
ll a[sz], b[sz], sim[sz], mx, LCM;

pll ext_gcd(ll a, ll b)   // returns x, y for ax + by = gcd(a,b)
{
    if(b == 0) return pll(1, 0);
    else
    {
        pll d = ext_gcd(b, a % b);
        return pll(d.ss, d.ff - d.ss * (a / b));
    }
}

/**
    A CRT solver which works even when moduli are not pairwise coprime
    1. Add equations using addEquation() method
    2. Call solve() to get {x, N} pair, where x is the unique solution modulo N.
    Assumptions:
        1. LCM of all mods will fit into long long.
*/
class ChineseRemainderTheorem {
    typedef long long vlong;

    /** CRT Equations stored as pairs of vector. See addEqation()*/
    vector<pll> equations;

public:
    void clear() {
        equations.clear();
    }

    /** Add equation of the form x = r (mod m)*/
    void addEquation( vlong r, vlong m ) {
        equations.push_back({r, m});
    }
    pll solve() {
        if (equations.size() == 0) return {-1,-1}; /// No equations to solve

        vlong a1 = equations[0].first;
        vlong m1 = equations[0].second;
        a1 %= m1;
        /** Initially x = a_0 (mod m_0)*/

        /** Merge the solution with remaining equations */
        for ( int i = 1; i < equations.size(); i++ ) {
            vlong a2 = equations[i].first;
            vlong m2 = equations[i].second;

            vlong g = __gcd(m1, m2);
            if ( a1 % g != a2 % g ) return {-1,-1}; /// Conflict in equations

            /** Merge the two equations*/
            vlong p, q;
            pll ret = ext_gcd(m1/g, m2/g);
            p = ret.first, q = ret.second;

            vlong mod = m1 / g * m2;
            vlong x = ( (__int128)a1 * (m2/g) % mod *q % mod + (__int128)a2 * (m1/g) % mod * p % mod ) % mod;

            /** Merged equation*/
            a1 = x;
            if ( a1 < 0 ) a1 += mod;
            m1 = mod;
        }
        return {a1, m1};
    }
};

ll solve(ll day)
{
    ll mat = 0, cnt = day/LCM, rest = day%LCM;

    for1(i, mx) {
        if(sim[i] == -1)
            continue;

        mat += cnt;
        if(sim[i] <= rest)
            mat++;
    }
    return (day+1)-mat;
}

int main()
{
    fastio;

    ll n, m, k;
    cin >> n >> m >> k;

    ms(sim, -1), ms(a,-1), ms(b,-1);

    for0(i, n) {
        int inp; cin >> inp;
        a[inp] = i;
    }

    for0(i, m) {
        int inp; cin >> inp;
        b[inp] = i;
    }
    mx = 2*max(n, m);
    LCM = (n*m) / __gcd(n,m);

    ChineseRemainderTheorem CRT = ChineseRemainderTheorem();

    for1(i, mx) {
        if(a[i] == -1 || b[i] == -1)
            continue;

        CRT.clear();
        CRT.addEquation(a[i], n);
        CRT.addEquation(b[i], m);

        pll got = CRT.solve();
        sim[i] = got.first;
    }

    ll lo = 1, hi = mx*k, ret;

    while(lo <= hi) {
        ll mid = (lo+hi)>>1;

        ll tot = solve(mid-1);

        if(tot >= k) {
            hi = mid-1;
            ret = mid;
        }
        else
            lo = mid+1;
    }
    cout << ret << EL;

    return 0;
}
