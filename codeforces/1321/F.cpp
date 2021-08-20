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

const ll sz = 2e5 + 10, base = 1e9+181, mod = 2e9+63;
char s[sz];
ll pw[sz], inv1;

ll fastPow(ll x, ll n, ll MOD)
{
    ll ret = 1;
    while (n)
    {
        if (n & 1) ret = (ret * x) % MOD;
        x = (x * x) % MOD;
        n >>= 1;
    }
    return ret % MOD;
}

struct seg {
    int len;
    bool be, en;
    ll hsh;
} tr[4*sz];

void build(int lo, int hi, int node)
{
    if(lo == hi) {
        tr[node].hsh = (s[lo] == '1') + 1;
        tr[node].len = 1;
        tr[node].be = tr[node].en = (s[lo] == '1');
        return;
    }

    int mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    build(lo, mid, lft);
    build(mid+1, hi, rgt);

    if(tr[lft].len == 0) {
        tr[node] = tr[rgt];
        return;
    }
    if(tr[rgt].len == 0) {
        tr[node] = tr[lft];
        return;
    }

    auto [len1, be1, en1, h1] = tr[lft];
    auto [len2, be2, en2, h2] = tr[rgt];

    if(en1 == 1 && be2 == 1) {

        tr[node].len = len1+len2-2;

        tr[node].be = (len1 == 1)? 0 : be1, tr[node].en = (len2==1)? 0 : en2;

        h1 = ((h1 - 2) * inv1) % mod;
        h2 = (h2 - 2*pw[len2 - 1]) % mod;
        if(h2 < 0) h2 += mod;

        tr[node].hsh = ((h1 * pw[len2-1]) + h2) % mod;
    }
    else {
        tr[node].len = len1+len2;
        tr[node].be = be1, tr[node].en = en2;
        tr[node].hsh = ((h1 * pw[len2]) + h2) % mod;
    }
}

seg qry(int lo, int hi, int l, int r, int node)
{
    if(lo > r || hi < l)
        return {0, 0, 0, 0};
    if(lo >= l && hi <= r) {
        //cerr << lo << " " << hi << " " << tr[node].hsh << endl;
        return tr[node];
    }

    int mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    seg p1 = qry(lo, mid, l, r, lft);
    seg p2 = qry(mid+1, hi, l, r, rgt);

    if(p1.len == 0) return p2;
    if(p2.len == 0) return p1;

    auto [len1, be1, en1, h1] = p1;
    auto [len2, be2, en2, h2] = p2;

    if(en1 == 1 && be2 == 1) {

        ll len = len1+len2-2;

        bool be = (len1 == 1)? 0 : be1, en = (len2==1)? 0 : en2;

        h1 = ((h1 - 2) * inv1) % mod;
        h2 = (h2 - 2*pw[len2 - 1]) % mod;
        if(h2 < 0) h2 += mod;

        ll hsh = ((h1 * pw[len2-1]) + h2) % mod;
        //cerr << lo << " " << hi << " || " << hsh << endl;

        return {len, be, en, hsh};
    }
    else {
        ll len = len1+len2;
        bool be = be1, en = en2;
        ll hsh = ((h1 * pw[len2]) + h2) % mod;

        //cerr << lo << " " << hi << " " << hsh << endl;

        return {len, be, en, hsh};
    }
}

int main()
{
    pw[0] = 1;
    for1(i, sz-1) pw[i] = (pw[i-1] * base) % mod;

    inv1 = fastPow(base, mod-2, mod);

    ll n; sl(n);
    scanf("%s", s+1);

    build(1, n, 1);
    //dbg(qry(1, n, 2, 4, 1).hsh);

    ll q; sl(q);

    while(q--) {
        ll l1, l2, len;
        sl(l1), sl(l2), sl(len);

        seg p1 = qry(1, n, l1, l1+len-1, 1);
        seg p2 = qry(1, n, l2, l2+len-1, 1);

        //dbg(mp(p1.hsh, p2.hsh));

        if(p1.hsh == p2.hsh) pf("Yes\n");
        else pf("No\n");
    }

    return 0;
}
