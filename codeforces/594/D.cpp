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

const ll sz = 2e5 + 10, mod = 1e9 + 7, MAX_N = 1e6 + 10;

ll ara[sz], ans[sz], BIT[sz], inv[MAX_N], inv2[MAX_N], cmul[sz];
bool chk[MAX_N];

vector <int> pfac[MAX_N], p[sz], pos[MAX_N];
vector <pii> qry[sz];

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

inline ll Inv(ll x) {return fastPow(x, mod-2, mod);}

void upd(ll idx, ll v, ll n)
{
    while(idx <= n) {
        BIT[idx] = (BIT[idx]*v) % mod;
        idx += idx&(-idx);
    }
}

ll query(ll idx)
{
    ll ret = 1;
    while(idx >= 1) {
        ret = (ret * BIT[idx]) % mod;
        idx -= idx&(-idx);
    }
    return ret;
}

ll query(ll l, ll r)
{
    return (query(r) * Inv(query(l-1)) ) % mod;
}

int main()
{
    for(int i = 2; i < MAX_N; i++) {
        if(!chk[i]) {
            for(int j = i; j < MAX_N; j += i) {
                pfac[j].pb(i);
                if(j != i) chk[j] = 1;
            }
        }
    }

    ll n; cin>>n;
    cmul[0] = 1;

    for1(i, n) {
        sl(ara[i]);
        p[i] = pfac[ ara[i] ];

        for(int &x : p[i])
            pos[x].pb(i);

        BIT[i] = 1;
        cmul[i] = (cmul[i-1] * ara[i]) % mod;
    }

    for(ll i = 2; i < MAX_N; i++) {
        pfac[i].clear();

        if(chk[i])
            continue;

        inv[i] = Inv(i);
        inv2[i-1] = Inv(i-1);

        if(!pos[i].empty()) {
            reverse(all(pos[i]));
            upd(pos[i].back(), ((i-1)*inv[i]) % mod, n);
        }
    }

    ll q; sl(q);

    for1(i, q) {
        ll l, r;
        sl(l), sl(r);

        qry[l].pb({r, i});
    }

    for1(i, n) {

        for(pii &pr : qry[i]) {
            ll got = query(i, pr.ff);
            ll mul = (cmul[pr.ff] * Inv(cmul[i-1])) % mod;
            got = (mul*got) % mod;

            ans[pr.ss] = got;
        }

        for(int &x : p[i]) {

            upd(i, (x*inv2[x-1]) % mod, n);
            pos[x].pop_back();

            if(!pos[x].empty())
                upd(pos[x].back(), ((x-1)*inv[x]) % mod, n);
        }
    }

    for1(i, q) pf("%lld\n", ans[i]);

    return 0;
}
