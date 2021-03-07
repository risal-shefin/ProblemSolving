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

const ll sz = 1e5 + 10;
char s[sz];
ll cnt[30], cnt2[30], ase[sz][30], rest[30];

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll k, n;
        sl(n), sl(k);

        scanf("%s", s+1);

        if(n % k != 0) {
            pf("-1\n");
            continue;
        }

        ms(cnt, 0);

        for0(i, 26) ase[n+1][i] = 0;

        rep1(i, n) {

            for0(j, 26)
                ase[i][j] = ase[i+1][j];

            cnt[ s[i] - 'a' ]++;
            ase[i][ s[i] - 'a']++;
        }

        bool ok = 1;
        for0(i, 26) {
            if(cnt[i] % k != 0) {
                ok = 0;
                break;
            }
        }

        if(ok) {
            pf("%s\n", s+1);
            continue;
        }

        rep1(i, n) {

            if(s[i] == 'z')
                continue;

            ll now = s[i] - 'a', nxt = -1, rest = n-i+1;

            for(ll j = now+1; j < 26; j++) {

                for0(jj, 26) cnt2[jj] = cnt[jj] - ase[i][jj];

                ll d = cnt2[j] / k;
                rest = n-i+1;
                ll full = (d+1)*k, need = full-cnt2[j];

                if(need > (n-i+1))
                    continue;

                nxt = j;
                cnt2[j] += need, rest -= need;
                ll got = 1;

                for0(jj, 26) {
                    if(cnt2[jj] % k == 0)
                        continue;

                    ll d = cnt2[jj] / k;
                    ll full = (d+1)*k, need = full-cnt2[jj];

                    if(need > rest) {
                        got = 0;
                        break;
                    }

                    //if(i == 3) cout << jj << " || " << full << " " << cnt2[jj] << " " << need << EL;
                    cnt2[jj] += need, rest -= need;
                    //cout << cnt2[jj] << EL;
                }
                if(!got)
                    continue;

                ok = 1;
                break;
            }
            if(!ok)
                continue;

            ll idx = i;
            s[idx++] = (nxt+'a'), cnt2[nxt]--;

            for0(j, 26) {

                ll age = cnt[j] - ase[i][j];
                ll ext = cnt2[j] - age;

                ext += rest;
                rest = 0;

                for1(jj, ext) s[idx++] = (j+'a');
            }
            break;
        }

        pf("%s\n", s+1);
    }

    return 0;
}
