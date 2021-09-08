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

const ll sz = 3e5 + 10;
pll ara[sz];

const bool cmp(const pll &a, const pll &b)
{
    if(a.ss == b.ss)
        return a.ff < b.ff;

    return a.ss < b.ss;
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {

        ll n, m, k;
        sl(n), sl(m), sl(k);

        set <int> lx, ly;

        for1(i, n) {
            ll x; sl(x);
            lx.insert(x);
        }

        for1(i, m) {
            ll y; sl(y);
            ly.insert(y);
        }

        vector <int> px, py;

        for1(i, k) {
            sl(ara[i].ff), sl(ara[i].ss);

            px.pb(ara[i].ff);
            py.pb(ara[i].ss);
        }
        sort(all(px)), sort(all(py));

        ll ans = 0;

        for1(i, k) {
            auto itx = lx.find(ara[i].ff), ity = ly.find(ara[i].ss);
            if(itx != lx.end() && ity != ly.end())
                continue;

            if(itx != lx.end()) {
                auto it1 = ly.lower_bound(ara[i].ss), it2 = ly.upper_bound(ara[i].ss);

                ll pos1 = 0, pos2 = (ll)py.size()-1;

                if(it1 != ly.begin()) {
                    --it1;
                    pos1 = upper_bound(all(py), *it1) - py.begin();
                }

                if(it2 != ly.end()) {
                    pos2 = lower_bound(all(py), *it2)-py.begin();
                    pos2--;
                }

                ans += (pos2 - pos1 +1);
                ans--;
            }
            else {
                auto it1 = lx.lower_bound(ara[i].ff), it2 = lx.upper_bound(ara[i].ff);

                ll pos1 = 0, pos2 = (ll)px.size()-1;

                if(it1 != lx.begin()) {
                    --it1;
                    pos1 = upper_bound(all(px), *it1) - px.begin();
                }

                if(it2 != lx.end()) {
                    pos2 = lower_bound(all(px), *it2)-px.begin();
                    pos2--;
                }

                ans += (pos2 - pos1 +1);
                ans--;
            }
        }

        sort(ara+1, ara+k+1);

        for1(i, k) {
            ll stop = i;
            auto it = ly.lower_bound(ara[i].ss);

            if(it != ly.end() && *it == ara[i].ss)
                continue;

            ll lim = inf;
            if(it != ly.end()) lim = *it;

            for(ll j = i+1; j <= k; j++) {
                if(ara[j].ff != ara[i].ff || ara[j].ss >= lim)
                    break;

                stop = j;
            }

            ll len = (stop-i+1), way = len*(len-1);
            ans -= way;

            i = stop;
        }

        sort(ara+1, ara+k+1, cmp);

        for1(i, k) {
            ll stop = i;
            auto it = lx.lower_bound(ara[i].ff);

            if(it != lx.end() && *it == ara[i].ff)
                continue;

            ll lim = inf;
            if(it != lx.end()) lim = *it;

            for(ll j = i+1; j <= k; j++) {
                if(ara[j].ss != ara[i].ss || ara[j].ff >= lim)
                    break;

                stop = j;
            }

            ll len = (stop-i+1), way = len*(len-1);
            ans -= way;

            i = stop;
        }

        pf("%lld\n", ans/2);
    }

    return 0;
}
