#include <bits/stdc++.h>

#define VI vector<int>
#define VII vector<pair<int,int>>

#define ms(a) memset( a, 0, sizeof( a ) )
#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define ROF(i,a,b) for(int i = a; i >= b; i--)
#define foreach(v, c) for( typeof( (c).begin() ) v = (c).begin(); v != (c).end(); ++v)

#define pb push_back
#define pp pair<int,int>
#define mp make_pair
#define fi first
#define se second

#define popcount __builtin_popcount
#define gcd __gcd
#define putchar(c) putchar_unlocked(c)
#define bit(n,i) ( n & ( 1 << i ) )
#define lsb(x) ( x & ( -x ) )

#define FIN(str) freopen(str,"r",stdin)
#define FOUT(str) freopen(str,"w",stdout)
#define Fin(str) ifstream(str)
#define Fout(str) ostream(str)
#define SYNC ios_base::sync_with_stdio(0);

#define ll long long
#define ull unsigned long long

inline void read( int &a )
{
    register char ch;
    a = 0;

    do
    {
        ch = getchar_unlocked();

    } while ( !isdigit( ch ) );

    do
    {
        a = a * 10 + ch - '0';
        ch = getchar_unlocked();

    } while( isdigit( ch ) );
}

inline void write( int a )
{
    char s[20];
    int i = 0;

    do
    {
        s[ i++ ] = a % 10 + '0';
        a /= 10;

    } while ( a );

    i--;

    while ( i >= 0 ) putchar_unlocked( s[ i-- ] );
}

#define INF (int)1e9
#define EPS 1e-9
#define Nmax (int)1e5+2
#define LgMax 20

using namespace std;

int N, T;
char str[Nmax];

int main()
{
    FIN("cifralipsa.in");
    FOUT("cifralipsa.out");

    scanf("%d\n", &T);

    while ( T-- )
    {
        scanf("%s\n", str);

        int nr = 0;

        ROF(i, strlen( str ) - 1, 0 )
            nr += ( str[i] - '0' );

        nr %= 9;
        nr = 9 - nr;

        printf("%d\n", nr);
    }

    return 0;
}
