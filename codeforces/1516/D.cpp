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

const ll sz = 1e5 + 10, LN = 18;
vector <int> pfac[sz], pos[sz];
bitset <sz> chk;
ll nxt[sz][LN], ara[sz];

int main()
{
    for(ll i = 2; i < sz; i++) {
        if(!chk[i]) {
            for(ll j = i; j < sz; j += i) {
                chk[j] = 1;
                pfac[j].pb(i);
            }
        }
    }

    ll n, q;
    cin >> n >> q;

    for1(i, n) {
        sl(ara[i]);

        for(int &p : pfac[ ara[i] ])
            pos[p].pb(i);
    }

    ms(nxt, -1);
    nxt[n][0] = n+1;

    rep1(i, n-1) {
        ll g = __gcd(ara[i], ara[i+1]);
        if(g != 1) {
            nxt[i][0] = i+1;
            continue;
        }

        ll d = nxt[i+1][0];
        for(int &p : pfac[ ara[i] ]) {
            ll idx = upper_bound(all(pos[p]), i) - pos[p].begin();

            if(idx < pos[p].size())
                d = min(d, (ll)pos[p][idx]);
        }

        nxt[i][0] = d;
    }

    for1(i, LN-1) {
        for1(j, n)
            if(nxt[j][i-1] != -1)
                nxt[j][i] = nxt[ nxt[j][i-1] ][i-1];
    }

    while(q--) {
        ll l, r;
        sl(l), sl(r);

        ll ans = 0, cur = l;

        rep0(i, LN) {
            if(nxt[cur][i] == -1 || nxt[cur][i] > r)
                continue;

            cur = nxt[cur][i];
            ans += (1LL<<i);
        }
        ans++;
        pf("%lld\n", ans);
    }

    return 0;
}
