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

const ll sz = 1e5 + 10;
ll ara[sz];

int main()
{
    ll t;
    cin >> t;

    while(t--) {

        set <int> bad, lst;
        vector <int> ans;

        ll n; sl(n);

        for1(i, n)
            sl(ara[i]);

        for1(i, n) {
            ll prv = i-1;
            if(prv < 1) prv = n;

            lst.insert(i);

            ll g = __gcd(ara[i], ara[prv]);
            if(g == 1)
                bad.insert(i);
        }
        //dbg(bad.size());

        ll now = 1;

        while(!bad.empty() && lst.size() > 2) {

            ll idx;

            auto it = bad.upper_bound(now);
            if(it == bad.end())
                idx = *bad.begin();
            else
                idx = *it;

            bad.erase(idx), lst.erase(idx);
            ans.pb(idx);

            ll p1, p2;
            auto it2 = lst.upper_bound(idx);
            if(it2 == lst.end())
                p2 = *lst.begin();
            else
                p2 = *it2;

            if(__gcd(ara[idx], ara[p2]) == 1)
                bad.erase(p2);

            now = p2;
            if(lst.size() <= 2) break;

            auto it3 = lst.lower_bound(idx);
            if(it3 == lst.begin())
                p1 = *lst.rbegin();
            else
                p1 = *(--it3);

            ll g = __gcd(ara[p1], ara[p2]);
            if(g == 1) bad.insert(p2);
        }

        if(lst.size() == 2) {
            ll p1 = *lst.begin(), p2 = *lst.rbegin();

            if(__gcd(ara[p1], ara[p2]) == 1) {
                if(now == p1) {
                    ans.pb(p2);
                    if(ara[p1] == 1) ans.pb(p1);
                }
                else {
                    ans.pb(p1);
                    if(ara[p2] == 1) ans.pb(p2);
                }
            }
        }
        if(lst.size() == 1 && ara[*lst.begin()] == 1)
            ans.pb(*lst.begin());

        pf("%lld", (ll)ans.size());
        for(int &x : ans) pf(" %d", x);
        pn;
    }

    return 0;
}
