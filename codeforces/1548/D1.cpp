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

ll cnt[4][4];
vector <pii> pnt;

inline ll sub(ll a, ll b) {
    ll d = a-b;
    if(d < 0) d += 4;
    return d;
}

// Pick's Theeorem: A = I + (B/2) -1 => I = A - (B/2) + 1
ll solve(pii p1, pii p2, pii p3)
{
    auto &[x1, y1] = p1; auto &[x2, y2] = p2; auto &[x3, y3] = p3;

    ll b1 = 0, b2 = 0, b3 = 0;
    if(sub(x2, x1)%4 != 0 || sub(y2, y1)%4 != 0) b1 = 2;
    if(sub(x3, x2)%4 != 0 || sub(y3, y2)%4 != 0) b2 = 2;
    if(sub(x3, x1)%4 != 0 || sub(y3, y1)%4 != 0) b3 = 2;

    ll B = b1 + b2 + b3;

    if(B%4 == 0) return 1;
    else return 0;
}

inline ll nC2(ll n) {return n*(n-1)/2;}
inline ll nC3(ll n) {return n*(n-1)*(n-2)/6;}

int main()
{
    for0(x, 4)
        for0(y, 4)
            pnt.pb({x, y});

    ll n;
    cin >> n;
    for1(i, n) {
        ll x, y;
        sl(x), sl(y);

        x%=4, y%=4;
        cnt[x][y]++;
    }

    ll ans = 0;

    for0(i, pnt.size()) {
        auto &[x1, y1] = pnt[i];

        ans += nC3(cnt[x1][y1]);

        for(ll j = i+1; j < pnt.size(); j++) {
            auto &[x2, y2] = pnt[j];

            ans += nC2(cnt[x1][y1]) * cnt[x2][y2] * solve(pnt[i], pnt[i], pnt[j]);
            ans += nC2(cnt[x2][y2]) * cnt[x1][y1] * solve(pnt[i],pnt[j], pnt[j]);

            for(ll k = j+1; k < pnt.size(); k++) {
                auto &[x3, y3] = pnt[k];

                ll way = cnt[x1][y1] * cnt[x2][y2] * cnt[x3][y3];
                ans += way * solve(pnt[i], pnt[j], pnt[k]);
            }
        }
    }

    cout << ans << EL;

    return 0;
}
