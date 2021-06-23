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

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

const ll sz = 4e5 + 10;
ll ara[sz], csum[sz], lg[sz];
unordered_map <int, int, custom_hash> last;

int main()
{
    //freopen("out.txt", "r", stdin);

    vector <int> lst;
    ll n, s;
    cin >> n >> s;
    s *= 8;

    for1(i, n) {
        sl(ara[i]);
        lst.pb(ara[i]);

        ll tmp = i, p = 0;

        for(ll j = 0; ;j++) {
            if((1LL<<j) >= tmp) {
                p = j;
                break;
            }
        }

        lg[i] = p;
    }

    sort(all(lst));
    lst.erase(unique(all(lst)), lst.end());
    sort(ara+1, ara+n+1);

    for1(i, n) {
        if(i == 1) csum[i] = 1;
        else csum[i] = csum[i-1] + (ara[i] != ara[i-1]);
    }

    rep1(i, n) {
        ll now = ara[i];
        if(last.find(now) != last.end())
            continue;

        last[ now ] = i;
    }

    ll ans = inf;

    for(ll i = 0; i < lst.size(); i++) {
        ll val = lst[i];
        ll l = lower_bound(ara+1, ara+n+1, val) - ara;
        ll c = l-1;

        ll lo = i, hi = lst.size()-1, ret = inf;

        while(lo <= hi) {
            ll mid = lo+hi>>1;

            ll v = lst[mid], r = last[v];
            ll unq = csum[r] - csum[l-1], c2 = n-r;

            if(lg[unq]*n <= s) {
                ret = c+c2;
                //if(l==1) dbg(unq);
                lo = mid+1;
            }
            else
                hi = mid-1;
        }

        //dbg(mp(l, ret));
        ans = min(ans, ret);
    }
    cout << ans << EL;

    return 0;
}

