#include <bits/stdc++.h>

#define VI                          vector<int>
#define VII                         vector<pair<int,int>>
#define QI                          queue<int>

#define ms(a)                       memset( a, 0, sizeof( a ) )
#define FOR(i,a,b)                  for(int i = a; i <= b; ++i)
#define ROF(i,a,b)                  for(int i = a; i >= b; i--)
#define foreach(v, c)               for( typeof( (c).begin() ) v = (c).begin();  v != (c).end(); ++v)

#define pb                          push_back
#define pp                          pair<int,int>
#define mp                          make_pair
#define fi                          first
#define se                          second

#define popcount                    __builtin_popcount
#define gcd                         __gcd
#define putchar(c)                  putchar_unlocked(c)
#define bit(n,i)                    ( n & ( 1 << i ) )
#define lsb(x)                      ( x & ( -x ) )

#define FIN(str)                    freopen(str,"r",stdin)
#define FOUT(str)                   freopen(str,"w",stdout)
#define Fin(str)                    ifstream(str)
#define Fout(str)                   ostream(str)
#define SYNC                        ios_base::sync_with_stdio(0);

#define ll                          long long
#define ull                         unsigned long long

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

#define INF                         (int)1e9
#define EPS                         1e-9
#define Nmax                        (int)1e5+2
#define LgMax                       20

using namespace std;

stack <int> S;
int A[Nmax], st[Nmax], dr[Nmax], ind[Nmax], sol[Nmax];
int N, M;

int cmp( int x, int y )
{
    return A[x] < A[y];
}

int bsearch( int key )
{
    int st = 1, dr = N, gasit = 0, m;

    while ( st <= dr )
    {
        m = ( st + dr ) / 2;

        if ( A[ ind[m] ] <= key )
        {
            gasit = ind[m];
            st = m + 1;
        }
        else
        {
            dr = m - 1;
        }
    }

    return sol[ gasit ];
}

int main()
{
    FIN("secvmax.in");
    FOUT("secvmax.out");

    read( N ); read( M );

    for ( int i = 1; i <= N; ++i )
    {
        read( A[i] );
        ind[i] = i;
    }

    for ( int i = 1; i <= N; ++i )
    {
        while ( !S.empty() && A[S.top()] <= A[i] )
        {
            dr[S.top()] = i - 1;
            S.pop();
        }

        if ( S.empty() )
            st[i] = 1;
        else
            st[i] = S.top() + 1;

        S.push( i );
    }

    while ( !S.empty() )
    {
        dr[S.top()] = N;
        S.pop();
    }

    for ( int i = 1; i <= N; ++i )
        sol[i] = dr[i] - st[i] + 1;

    sort( ind + 1, ind + N + 1, cmp );

    for ( int i = 1; i <= N; ++i )
        sol[ ind[i] ] = max( sol[ ind[i] ], sol[ ind[i - 1] ] );

    for ( int i = 1, a; i <= M; ++i )
    {
        read( a );
        write( bsearch( a ) );
        putchar( '\n' );
    }

    return 0;
}
