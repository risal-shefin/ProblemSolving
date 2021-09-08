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

const ll sz = 50, mod = 998244353;
ll pos[sz], k, h, A, n, lev[sz], ok, pw[sz], half;
unordered_map <ll, unordered_map<ll, vector<int>> > rest;
vector <ll> other;
ll iter;

void solve1(ll x, ll msk, ll hsh)
{
    if(ok) return;

    if(x == 1) {
        ll frst;
        for0(i, half) {
            if(msk>>i & 1)
                frst = i;
        }

        vector <int> v;
        for0(i, half) v.pb(pos[i]);

        rest[frst][hsh] = v;
        return;
    }

    vector <pii> lst;
    ll x1 = -1;

    for0(i, half) {
        if((msk>>i) & 1) {
            if(x1==-1) x1 = i;
            else {
                lst.pb(mp(x1, i));
                x1 = -1;
            }
        }
    }

    ll lim = 1 << lst.size();
    int pos2[half];

    for0(i, lim) {

        ll nmsk = msk, cur = hsh;
        for0(j, half) pos2[j] = pos[j];

        for0(j, lst.size()) {

            auto &[a, b] = lst[j];

            if((i>>j) & 1) {
                nmsk ^= (1<<a);
                pos[a] = lev[x], cur = (cur + (a+1)*pw[ pos[a] ]) % mod;
            }
            else {
                nmsk ^= (1<<b);
                pos[b] = lev[x], cur = (cur + (b+1)*pw[ pos[b] ]) % mod;;
            }
        }

        solve1(x-1, nmsk, cur);

        for0(j, half) pos[j] = pos2[j];
    }
}

inline ll make_Hash(ll hsh, ll p1, ll p2)
{
    hsh = (hsh + p1*pw[1]) % mod;
    hsh = (hsh + p2*pw[2]) % mod;
    return hsh;
}

inline bool doExist(ll hsh, ll ph)
{
    auto it = rest[ph].find(hsh);
    return it != rest[ph].end();
}

void solve2(ll x, ll msk, ll hsh)
{
    if(ok) return;

    if(x == 1) {
        ll frst;
        for(int i = half; i < n; i++) {
            if((msk>>i) & 1)
                frst = i;
        }

        for0(i, half) {
            ll cur = make_Hash(hsh, frst+1, i+1), need = (h-cur);
            if(need < 0) need += mod;

            if(!doExist(need, i))
                continue;

            auto it = rest[i].find(need);

            for0(j, half) pos[j] = it->second[j];
            pos[i] = 2, pos[frst] = 1, ok = 1;

            return;
        }

        for0(i, half) {
            ll cur = make_Hash(hsh, i+1, frst+1), need = (h-cur);
            if(need < 0) need += mod;

            if(!doExist(need, i))
                continue;

            auto it = rest[i].find(need);

            for0(j, half) pos[j] = it->second[j];
            pos[i] = 1, pos[frst] = 2, ok = 1;

            return;
        }

        return;
    }

    vector <pii> lst;
    ll x1 = -1;

    for(int i = half; i < n; i++) {
        if((msk>>i) & 1) {
            if(x1==-1) x1 = i;
            else {
                lst.pb(mp(x1, i));
                x1 = -1;
            }
        }
    }

    ll lim = 1 << lst.size();
    int pos2[n];

    for0(i, lim) {

        ll nmsk = msk, cur = hsh;
        for(int j=half; j < n; j++) pos2[j] = pos[j];

        for0(j, lst.size()) {

            auto &[a, b] = lst[j];

            if((i>>j) & 1) {
                nmsk ^= (1<<a);
                pos[a] = lev[x], cur = (cur + (a+1)*pw[ pos[a] ]) % mod;
            }
            else {
                nmsk ^= (1<<b);
                pos[b] = lev[x], cur = (cur + (b+1)*pw[ pos[b] ]) % mod;;
            }
        }

        solve2(x-1, nmsk, cur);
        if(ok) return;

        for(int j=half; j < n; j++) pos[j] = pos2[j];
    }
}

int main()
{
    cin >> k >> A >> h;

    pw[0] = 1;
    for1(i, sz-1) pw[i] = (pw[i-1] * A) % mod;

    lev[0] = 1, lev[1] = 2;

    for(ll i = 2; i <= k; i++)
        lev[i] = (1LL << (i-1)) + 1;

    n = 1LL<<k, half = n/2;

    solve1(k, (1LL<<half)-1, 0);

    solve2(k, ((1LL<<n)-1) ^ ((1LL<<half)-1), 0);

    if(ok) {
        for0(i, n) pf("%lld ", pos[i]);
        pn;
    }
    else
        pf("-1\n");

    return 0;
}

