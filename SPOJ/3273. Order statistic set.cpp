#include <bits/stdc++.h>

#define VI vector<int>
#define VII vector<pair<int,int>>
#define QI queue<int>

#define ms(a,v) memset( a, v, sizeof( a ) )
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
        ch = getchar();

    } while ( !isdigit( ch ) );

    do
    {
        a = a * 10 + ch - '0';
        ch = getchar();

    } while( isdigit( ch ) );
}

inline void write( int a )
{
    char s[20];
    int i = 0;
    int sign = 1;

    if ( a < 0 )
        sign = -1,
        a = -a;

    do
    {
        s[ i++ ] = a % 10 + '0';
        a /= 10;

    } while ( a );

    i--;

    if ( sign == -1 )
        putchar( '-' );

    while ( i >= 0 ) putchar( s[ i-- ] );
}

const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, 1, 0, -1 };

const int dl[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

const int INF = 2e9;
const double EPS = 1e-9;

const int Nmax = 1e4 + 2;

const int LgMax = log2(Nmax) + 1;

using namespace std;

struct Treap
{
    int priority,nr_nodes,key;

    Treap *st, *dr;

    Treap( const int _key, const int _priority, const int _nr_nodes, Treap *_st, Treap *_dr )
    {
        key = _key;
        priority = _priority;
        nr_nodes = _nr_nodes;
        st = _st;
        dr = _dr;
    }
};

Treap *NIL, *root;

void initTreap()
{
    srand( time( NULL ) );
    NIL = new Treap( 0, 0, 0, NULL, NULL );
    root = NIL;
}

void update( Treap *&T )
{
    T->nr_nodes = 1 + T->st->nr_nodes + T->dr->nr_nodes;
}

void rotateRight( Treap *&T )
{
    Treap *aux = T->st;
    T->st = aux->dr;
    aux->dr = T;

    update( T );
    update( aux );

    T = aux;
}

void rotateLeft( Treap *&T )
{
    Treap *aux = T->dr;
    T->dr = aux->st;
    aux->st = T;

    update( T );
    update( aux );

    T = aux;
}

void balance( Treap *&T )
{
    if ( T->st->priority > T->priority )
        rotateRight( T );

    if ( T->dr->priority > T->priority )
        rotateLeft( T );

    update( T );
}

void insert( Treap *&T, int key, int p = rand() + 1 )
{
    if ( T == NIL )
    {
        T = new Treap( key, p, 1, NIL, NIL );
    }
    else
    {
        if ( key < T->key )
            insert( T->st, key, p );
        else
            if ( key > T->key )
                insert( T->dr, key, p );

        balance( T );
    }
}

void erase( Treap *&T, int key )
{
    if ( T == NIL ) return;

    if ( key < T->key )
        erase( T->st, key );
    else
        if ( key > T->key )
            erase( T->dr, key );
        else
        {
            if ( T->st == NIL && T->dr == NIL )
            {
                delete T;
                T = NIL;
            }
            else
            {
                if ( T->st->priority > T->dr->priority )
                {
                    rotateRight( T );
                    erase( T->dr, key );
                }
                else
                {
                    rotateLeft( T );
                    erase( T->st, key );
                }
            }
        }

    if ( T != NIL )
        update( T );
}

int find( Treap *T, int key )
{
    if ( T == NIL )      return 0;
    if ( T->key == key ) return 1;
    if ( key < T->key )  return find( T->st, key );
    else                 return find( T->dr, key );
}

int Kth( Treap *T, int position )
{
    if ( T->st->nr_nodes + 1 == position ) return T->key;
    if ( position <= T->st->nr_nodes )     return Kth( T->st, position );
    else                                   return Kth( T->dr, position - 1 - T->st->nr_nodes );
}

int Count( Treap* T, int key )
{
    if ( T == NIL ) return 0;

    if ( key > T->key )
        return 1 + T->st->nr_nodes + Count( T->dr, key );
    else
        return Count( T->st, key );
}

int main()
{
    ///FIN("data.in");

    int Q, val;
    char type;

    initTreap();

    scanf("%d\n", &Q);

    while ( Q-- )
    {
        scanf("%c %d\n", &type, &val);

        if ( type == 'I' )
        {
            insert( root, val );
        }

        if ( type == 'D' )
        {
            erase( root, val );
        }

        if ( type == 'K' )
        {
            if ( val > root->nr_nodes )
                puts("invalid");
            else
            {
                write( Kth( root, val ) );
                putchar( '\n' );
            }
        }

        if ( type == 'C' )
        {
            write( Count( root, val ) );
            putchar( '\n' );
        }
    }
}

