#include <bits/stdc++.h>

using namespace std;

const int Vmax = 100000 + 1;
const int Emax = 200000 + 1;

struct Graph
{
    struct Node
    {
        int nod;
        int next;
    };

    Node listEdges[Emax];
    int head[Vmax];
    int contor;

    Graph()
    {
        contor = 0;

        for ( int i = 0; i < Vmax; ++i )
            head[i] = 0;
    }

    void addEdge( int a, int b )
    {
        contor++;
        listEdges[contor].nod = b;
        listEdges[contor].next = head[a];
        head[a] = contor;
    }
};

Graph G;
bool visited[Vmax];
int nrSCC[Vmax];

int lowLink[Vmax];
int Index[Vmax];
int Stack[Vmax], top;
bool onStack[Vmax];

int N, M, P, I;

Graph SCC;
int numberOfSCC;

void DFS(int nod)
{
    visited[nod] = true;
    Index[nod] = lowLink[nod] = ++I;
    Stack[ ++top ] = nod;
    onStack[nod] = true;

    for ( int p = G.head[nod]; p != 0; p = G.listEdges[p].next )
    {
        int v = G.listEdges[p].nod;

        if ( visited[v] == false )
        {
            DFS(v);
            lowLink[nod] = min(lowLink[nod], lowLink[v]);
        }
        else
            if ( onStack[v] )
                lowLink[nod] = min(lowLink[nod], lowLink[v]);
    }

    if ( lowLink[nod] == Index[nod] )
    {
        numberOfSCC++;
        int v;

        do
        {
            v = Stack[ top-- ];
            onStack[v] = false;

            SCC.addEdge(numberOfSCC, v);
            nrSCC[v] = numberOfSCC;

        } while ( v != nod );
    }
}

void Tarjan()
{
    for ( int i = 1; i <= N; ++i )
        if ( visited[i] == false )
            DFS(i);
}

int main()
{
    ios_base::sync_with_stdio( false );

    cin >> N >> M;

    for ( int i = 1; i <= M; ++i )
    {
        int a, b;
        cin >> a >> b;

        G.addEdge(a, b);
    }

    Tarjan();

    cout << numberOfSCC << "\n";

    for ( int i = 1; i <= numberOfSCC; ++i )
    {
        for ( int p = SCC.head[i]; p != 0; p = SCC.listEdges[p].next )
            cout << SCC.listEdges[p].nod << " ";

        cout << "\n";
    }

    return 0;
}
