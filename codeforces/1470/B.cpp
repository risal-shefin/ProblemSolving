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

#define ff first
#define ss second
const ll sz = 3e5 + 10, MAX_N = 1e6+10;
vector <int> pfac[MAX_N];
bool chk[MAX_N];
map <vector<int>, int> track;

int main()
{
    for(ll i = 2; i < MAX_N; i++) {
        if(!chk[i]) {
            for(ll j = i; j < MAX_N; j += i) {
                chk[j] = 1;

                int tmp = j, cnt = 0;
                while(tmp % i == 0) tmp /= i, cnt++;

                if(cnt & 1) pfac[j].pb(i);
            }
        }
    }

    ll t;
    cin >> t;
    while(t--) {
        ll n; sl(n);

        for1(i, n) {
            ll inp; sl(inp);
            ++track[ pfac[inp] ];
        }

        ll ans1 = 0, ans2 = 0, even = 0;

        for(auto it = track.begin(); it != track.end(); ++it) {
            ans1 = max(ans1, (ll)it->second);
            ans2 = max(ans2, ans1);

            if(it->first.empty() || it->second % 2 == 0)
                even += (it->second);
        }
        ans2 = max(ans2, even);

        ll q; sl(q);
        while(q--) {
            ll w; sl(w);
            if(w == 0) pf("%lld\n", ans1);
            else pf("%lld\n", ans2);
        }
        track.clear();
    }

    return 0;
}