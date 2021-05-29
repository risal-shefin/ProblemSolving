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

const ll sz = 1e5 + 10;
int BIT[sz], cnt[26];
vector <int> pos[26];
string s;

void upd(int idx, int n)
{
    while(idx <= n) {
        BIT[idx]++;
        idx+=idx&(-idx);
    }
}

ll qry(ll idx)
{
    ll ret = 0;
    while(idx > 0) {
        ret += BIT[idx];
        idx-=idx&(-idx);
    }
    return ret;
}

ll query(ll l, ll r)
{
    return qry(r) - qry(l-1);
}

ll solve(const vector <char> &v)
{
    for1(i, s.size()) BIT[i] = 0;

    ll ptr = 0, cst = 0;

    for0(i, 4) {
        ll now = v[i] - 'A', id = 0;

        for1(j, cnt[now]) {
            ll p = pos[now][id++];
            ll fwd = query(p, s.size());

            ptr++;
            cst += (p+fwd)-ptr;
            upd(p, s.size());
        }
    }
    return cst;
}

int main()
{
    fastio;

    ll t;
    cin >> t;

    while(t--) {
        cin >> s;

        for(ll i = 0; i < s.size(); i++) {
            ll now = s[i] - 'A';
            cnt[now]++;
            pos[now].pb(i+1);
        }

        ll ans = -inf;
        vector <char> v = {'A', 'N', 'O', 'T'}, got;
        do {

            ll swp = solve(v);
            if(swp > ans) {
                ans = swp;
                got = v;
            }

        } while(next_permutation(all(v)));

        for0(i, 4) {
            ll now = got[i] - 'A';
            for1(j, cnt[now]) cout << got[i];

            cnt[now] = 0;
            pos[now].clear();
        }
        cout << EL;
        //dbg(ans);
    }

    return 0;
}
