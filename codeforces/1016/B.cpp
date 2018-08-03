#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll process[1009][1009];

void findAllOccurances(std::string data, std::string toSearch)
{
	// Get the first occurrence
	size_t pos = data.find(toSearch);

	// Repeat till end is reached
	while( pos != std::string::npos)
	{

        for(ll i = pos + toSearch.size() - 1; i < data.length(); i++)
            process[pos + 1][i + 1] = 1;

		// Get the next occurrence from the current position
		pos =data.find(toSearch, pos + 1);
	}

	//cout << 5;
}

int main()

{
    std::ios_base::sync_with_stdio(false);
    string s, t;
    ll n, m, q;
    cin >> n >> m >> q;
    cin >> s >> t;

	findAllOccurances(s , t);

    while(q--) {
        ll x, y;
        cin >> x >> y;
        ll ans = 0;
        for(ll i = x; i <= y; i++)
            if(process[i][y] == 1)
                ans++;
        cout << ans << endl;
    }

    return 0;
}
