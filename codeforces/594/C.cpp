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

const ll sz = 1e5 + 10;

struct info {
    int ff, ss;
} ara[sz];

ll ans = inf;

struct cmpw {
    const bool operator()(const int &a, const int &b)
    {
        if(ara[a].ff != ara[b].ff)
            return ara[a].ff < ara[b].ff;
        else
            return a < b;
    }
};

struct cmph {
    const bool operator()(const int &a, const int &b)
    {
        if(ara[a].ss != ara[b].ss)
            return ara[a].ss < ara[b].ss;
        else
            return a < b;
    }
};

set <int, cmpw> w;
set <int, cmph> h;

void solve(ll k)
{
    if(w.size() == 1 || h.size() == 1) {
        ans = 1;
        return;
    }
    if(k == 0) {
        ll dw = max(1, (ara[*w.rbegin()].ff  - ara[*w.begin()].ff)/2);
        ll dh = max(1, (ara[*h.rbegin()].ss  - ara[*h.begin()].ss)/2);

        ans = min(ans, (ll)dw*dh);
        //dbg(mp(dw, dh));
        return;
    }

    ll x = *w.begin();
    w.erase(x), h.erase(x);
    solve(k-1);
    w.insert(x), h.insert(x);

    x = *w.rbegin();
    w.erase(x), h.erase(x);
    solve(k-1);
    w.insert(x), h.insert(x);

    x = *h.begin();
    w.erase(x), h.erase(x);
    solve(k-1);
    w.insert(x), h.insert(x);

    x = *h.rbegin();
    w.erase(x), h.erase(x);
    solve(k-1);
    w.insert(x), h.insert(x);
}

int main()
{
    ll n, k;
    cin >> n >> k;
    for1(i, n) {
        ll x1, y1, x2, y2;
        scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);

        x1 *= 2, x2 *= 2, y1 *= 2, y2 *= 2;

        ara[i] = {(x1+x2)/2, (y1+y2)/2};
        w.insert(i), h.insert(i);
    }

    solve(k);

    cout << ans << EL;

    return 0;
}

