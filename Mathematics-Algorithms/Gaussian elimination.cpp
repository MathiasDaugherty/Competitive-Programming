#include <bits/stdc++.h>

using namespace std;

const int NR_EQUATIONS = 300 + 1;
const int NR_VARIABLES = 300 + 1;
const double EPS = 1e-10;

double A[NR_EQUATIONS][NR_VARIABLES + 1];
double solution[NR_VARIABLES];

bool isSolution = true;
int N, M;

void gaussian()
{
    int i = 1, j = 1;

    while (i <= N && j <= M)
    {
        int x = 0;

        for ( int k = i; k <= N; ++k )
        {
            if ( A[k][j] > EPS || A[k][j] < -EPS )
            {
                x = k;
                break;
            }
        }

        if ( !x )
        {
            j++;
            continue;
        }

        swap(A[i], A[x]);

        for ( int k = j + 1; k <= M + 1; ++k )
            A[i][k] /= A[i][j];

        A[i][j] = 1;

        for ( int l = i + 1; l <= N; ++l )
        {
            for ( int c = j + 1; c <= M + 1; ++c )
                A[l][c] -= A[i][c] * A[l][j];

            A[l][j] = 0;
        }

        i++; j++;
    }
}

void findSolutions()
{
    for ( int i = N; i >= 1; i-- )
        for ( int j = 1; j <= M + 1; ++j )
            if ( A[i][j] > EPS || A[i][j] < -EPS )
            {
                if ( j == M + 1 )
                {
                    isSolution = false;
                    return;
                }

                solution[j] = A[i][M + 1];

                for ( int k = j + 1; k <= M; ++k )
                    solution[j] -= A[i][k] * solution[k];

                break;
            }
}

int main()
{
    scanf("%d %d", &N, &M);

    for ( int i = 1; i <= N; ++i )
        for ( int j = 1; j <= M + 1; ++j )
            scanf("%lf ", &A[i][j]);

    gaussian();
    findSolutions();

    if ( isSolution )
    {
        for ( int i = 1; i <= M; ++i )
            printf("%.10lf ", solution[i]);

        printf("\n");
    }
    else
        printf("Imposibil\n");

    return 0;
}
