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

const ll sz = 3e5 + 10;
ll ara[sz];
set <int> pos[2][2];
char ori[sz];
map <int, int> ans;

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n, m;
        sl(n), sl(m);

        for1(i, n) sl(ara[i]);

        for1(i, n) {
            char ch; scanf(" %c", &ch);
            ori[i] = ch;

            bool odd = ara[i]&1;

            if(ch == 'L') pos[0][odd].insert(ara[i]);
            else pos[1][odd].insert(ara[i]);
        }

        for0(x, 2) {
            if(pos[1][x].empty()) continue;
            bool done = 0;

            for(auto it = --pos[1][x].end(); !pos[1][x].empty() && !done;) {
                auto it2 = it;
                if(it != pos[1][x].begin()) it--;

                done |= (it2 == pos[1][x].begin());

                auto it3 = pos[0][x].upper_bound(*it2);
                if(it3 == pos[0][x].end()) {
                    if(it2 == pos[1][x].begin())
                        break;
                    continue;
                }

                ll T = abs(*it2 - *it3) / 2;
                ans[*it2] = ans[*it3] = T;

                pos[0][x].erase(it3);
                pos[1][x].erase(*it2);
            }
        }

        for0(x, 2) {

            for(auto it = pos[0][x].begin(); it != pos[0][x].end(); ) {
                auto it2 = it++;

                if(it == pos[0][x].end())
                    break;

                auto it3 = it++;

                ll T = *it2 + (*it3 - *it2) / 2; //dbg(T);
                ans[*it2] = ans[*it3] = T;

                pos[0][x].erase(it3);
                pos[0][x].erase(*it2);
            }

            if(pos[1][x].empty()) continue;
            bool done = 0;

            for(auto it = --pos[1][x].end(); !pos[1][x].empty() && !done;) {
                auto it2 = it;

                if(it == pos[1][x].begin()) break;
                it--;

                done |= (it == pos[1][x].begin());

                auto it3 = it;
                if(it != pos[1][x].begin()) it--;

                ll T = (m- *it2) + (*it2 - *it3) / 2;
                ans[*it2] = ans[*it3] = T;
                //dbg(mp(ans[9], ans[11]));

                pos[1][x].erase(it3);
                pos[1][x].erase(*it2);
            }
        }

        for0(x, 2) {
            for(auto it = pos[0][x].begin(); it != pos[0][x].end(); ) {
                auto it2 = it;
                it++;

                if(pos[1][x].empty()) break;

                auto it3 = pos[1][x].rbegin();

                ll p1 = *it2, p2 = *it3, mx = max(p1, m-p2);
                p1 -= mx, p2 += mx;
                if(p1 < 0) p1 = abs(p1);
                if(p2 > m) p2 = m - (p2-m);

                ll T = mx + (p2-p1)/2;
                ans[*it2] = ans[*it3] = T;

                pos[1][x].erase(*it3);
                pos[0][x].erase(*it2);
            }
        }

        for1(i, n) {
            if(ans.find(ara[i]) == ans.end()) pf("-1 ");
            else pf("%d ", ans[ara[i]]);
        }
        pn;

        ans.clear();
        for0(i, 2)
            for0(j, 2)
                pos[i][j].clear();
    }

    return 0;
}
