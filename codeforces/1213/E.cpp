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

bool vis[5][5];
ll n;

inline char other(char ch1, char ch2)
{
    char ret;
    for(char c = 'a'; c <= 'c'; c++) {
        if(c != ch1 && c != ch2) {
            ret = c;
            break;
        }
    }
    return ret;
}

void palt(char ch1, char ch2, char ch3)
{
    cout << "YES\n";
    for1(i, n) cout << ch1 << ch2;
    for1(i, n) cout << ch3;
    cout << EL;
}

int main()
{
    fastio;

    cin >> n;

    string s, t;
    cin >> s >> t;

    set <char> a, b;

    for(char &ch : s) a.insert(ch);
    for(char &ch : t) b.insert(ch);

    if(a.size() > b.size()) {
        swap(a, b);
        swap(s, t);
    }

    if(a.size() == 1 && b.size() == 1) {
        char ch1 = s[0], ch2 = t[0], ch3;

        ch3 = other(ch1, ch2);

        if(ch1 == ch2) ch2 = other(ch1, ch3);

        palt(ch1, ch2, ch3);
        return 0;
    }
    else if(a.size() == 1 && b.size() == 2) {
        char ch1 = s[0], ch2 = t[0], ch3 = t[1];

        if(ch1 == ch2) {
            ch2 = other(ch1, ch3);

            palt(ch1, ch2, ch3);
            return 0;
        }

        ch3 = other(ch1, ch2);
        palt(ch1, ch3, ch2);
        return 0;
    }
    else {

        ll f1 = -1, f2 = -1, f3 = -1;

        vis[s[0]-'a'][s[1]-'a'] = 1;
        vis[t[0]-'a'][t[1]-'a'] = 1;

        for0(i, 3) {
            for0(j, 3) {
                for0(k, 3) {
                    if(i == j || i == k || j == k)
                        continue;

                    if(vis[i][j] || vis[j][k])
                        continue;

                    f1 = i, f2 = j, f3 = k;
                    break;
                }
                if(f1 != -1) break;
            }
            if(f1 != -1) break;
        }

        if(f1 == -1) {
            cout << "NO\n";
            return 0;
        }

        cout << "YES\n";
        for1(i, n) cout << (char)(f1+'a');
        for1(i, n) cout << (char)(f2+'a');
        for1(i, n) cout << (char)(f3+'a');
        cout << EL;

        return 0;
    }

    return 0;
}
