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
#define inf (1LL << 62)
#define loop(i, start, stop, inc) for(ll i = start; i <= stop; i += inc)
#define for1(i, stop) for(ll i = 1; i <= stop; i++)
#define for0(i, stop) for(ll i = 0; i < stop; i++)
#define rep1(i, start) for(ll i = start; i >= 1; i--)
#define rep0(i, start) for(ll i = (start-1); i >= 0; i--)
#define ms(n, i) memset(n, i, sizeof(n))
#define casep(n) printf("Case %lld:", ++n)
#define pn printf("\n")
#define pf printf
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

const ll mod1 = 1e9 + 93, mod2 = 1e9 + 181, sz = 1e6 + 10;
const ll base1 = 193, base2 = 181;
char s[sz];
unordered_map <ll, int> pre1, pre2;
ll hsh1[sz], hsh2[sz], rev1[sz], rev2[sz];
ll pw1[sz], pw2[sz];

int main()
{
    pw1[0] = pw2[0] = 1;
    for(ll i = 1; i < sz; i++) {
        pw1[i] = (pw1[i-1] * base1) % mod1;
        pw2[i] = (pw2[i-1] * base2) % mod2;
    }

    ll t;
    cin >> t;
    while(t--) {
        scanf("%s", s+1);
        ll len = strlen(s+1);

        for(ll i = 1; i <= len; i++) {
            hsh1[i] = (hsh1[i-1] * base1 + (s[i] - 'a' + 1) ) % mod1;
            hsh2[i] = (hsh2[i-1] * base2 + (s[i] - 'a' + 1) ) % mod2;

            pre1[hsh1[i] ] = i;
            pre2[hsh2[i] ] = i;
        }

        ll mx = 0, p=-1, sf=-1;
        rev1[len+1] = rev2[len+1] = 0;
        for(ll i = len; i >= 1; i--) {
            rev1[i] = (rev1[i+1] * base1 + (s[i] - 'a' + 1) ) % mod1;
            rev2[i] = (rev2[i+1] * base2 + (s[i] - 'a' + 1) ) % mod2;

            ll h1 = hsh1[len] - (hsh1[i-1] * pw1[len-i+1]) % mod1;
            if(h1 < 0) h1 += mod1;
            ll h2 = hsh2[len] - (hsh2[i-1] * pw2[len-i+1]) % mod2;
            if(h2 < 0) h2 += mod2;

            //cout << rev1[i] << " " << h1 << " " << i << endl;

            if(h1 == rev1[i] && h2 == rev2[i]) {
                ll l = len-i+1;
                if(l > mx) {
                    mx = l;
                    p = -1, sf = i;
                }
            }


            for(ll j = 1; j < i; j++) {
                ll mh1 = (hsh1[j] * pw1[len-i+1] + h1) % mod1;
                ll mh2 = (hsh2[j] * pw2[len-i+1] + h2) % mod2;
            }
        }

        for(ll i = len; i >= 1; i--) {

            ll h1 = hsh1[len] - (hsh1[i-1] * pw1[len-i+1]) % mod1;
            if(h1 < 0) h1 += mod1;
            ll h2 = hsh2[len] - (hsh2[i-1] * pw2[len-i+1]) % mod2;
            if(h2 < 0) h2 += mod2;

            for(ll j = 1; j < i; j++) {
                ll mh1 = (hsh1[j] * pw1[len-i+1] + h1) % mod1;
                ll mh2 = (hsh2[j] * pw2[len-i+1] + h2) % mod2;

                ll rh1 = rev1[1] - (rev1[j+1] * pw1[j] ) % mod1;
                if(rh1 < 0) rh1 += mod1;
                ll rh2 = rev2[1] - (rev2[j+1] * pw2[j] ) % mod2;
                if(rh2 < 0) rh2 += mod2;

                ll rmh1 = (rev1[i] * pw1[j] + rh1) % mod1;
                ll rmh2 = (rev2[i] * pw2[j] + rh2) % mod2;

                if(mh1 == rmh1 && mh2 == rmh2) {
                    ll l = j + (len - i + 1);
                    if(l > mx) {
                        mx = l;
                        p = j, sf = i;
                    }
                }
            }
        }

        for1(i, len) {
            ll rh1 = rev1[1] - (rev1[i+1] * pw1[i]) % mod1;
            if(rh1 < 0) rh1 += mod1;
            ll rh2 = rev2[1] - (rev2[i+1] * pw2[i]) % mod2;
            if(rh2 < 0) rh2 += mod2;

            if(hsh1[i] == rh1 && hsh2[i] == rh2) {
                if(i > mx) {
                    mx = i;
                    p = i, sf = -1;
                }
            }
        }

        //cout << p << " " << sf << endl;
        if(p == -1) {
            for(ll i = sf; i <= len; i++)
                pf("%c", s[i]);
        }
        else if(sf == -1) {
            for(ll i = 1; i <= p; i++)
                pf("%c", s[i]);
        }
        else {
            for(ll i = 1; i <= p; i++)
                pf("%c", s[i]);
            for(ll i = sf; i <= len; i++)
                pf("%c", s[i]);
        }
        pn;

        pre1.clear(), pre2.clear();
    }

    return 0;
}

