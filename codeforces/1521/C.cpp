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

const ll sz = 1e4 + 10;
ll ara[sz];

inline ll ask(ll t, ll i, ll j, ll x)
{
    cout << "? " << t << " " << i << " " << j << " " << x << endl;
    ll ret; cin >> ret;
    assert(ret != -1);
    return ret;
}

int main()
{
    fastio;
    ll t; cin >> t;

    while(t--) {
        ll n; cin >> n;

        vector <ll> lst;

        for(ll i = 1; i < n; i += 2) {
            ll ret = ask(2, i, i+1, 1);

            if(ret == 1) lst.pb(i);
            else if(ret == 2) lst.pb(i+1);
        }

        if(n & 1) {
            for1(i, n-1) {

                ll ok = 1;
                for(ll &x : lst) {
                    if(x == i) {
                        ok = 0;
                        break;
                    }
                }
                if(!ok) continue;

                ll ret = ask(2, n, i, 1);
                if(ret == 1) lst.pb(n);
                break;
            }
        }

        ll one;
        if(lst.size() == 1) one = lst.back();
        else {
            ll ret = ask(2, lst[0], lst[1], 1);

            if(ret == 2) one = lst[1];
            else one = lst[0];
        }

        ara[one] = 1;

        for1(i, n) {
            if(i == one)
                continue;

            ll ret = ask(1, one, i, n-1);
            ara[i] = ret;
        }

        cout << "!";
        for1(i, n) cout << " " << ara[i];
        cout << endl;
    }

    return 0;
}
