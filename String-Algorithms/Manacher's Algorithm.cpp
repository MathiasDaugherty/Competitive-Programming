#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int Lmax = 1000 + 2;

char S[Lmax];      /// original string
char SS[2 * Lmax]; /// transformed string
int N, NN; /// lengths

int P[2 * Lmax]; /// P[i] = length of the longest palindrome centered at position i

void transform()
{
    /**
        First, we transform the input string, S, to another string SS by inserting a special character ‘$’ in between letters.
        This way, both palindromes of odd and even lengths will become odd length palindromes.
    **/

    SS[0] = '@'; /// we add special characters at the ends to prevent array overflow

    SS[ ++NN ] = '$'; /// '$' character which does not appear in S

    for ( int i = 1; i <= N; ++i )
    {
        SS[ ++NN ] = S[i];
        SS[ ++NN ] = '$';
    }

    SS[NN + 1] = '#';
}

void Manacher()
{
    int indexOfLongestPalindrome = 0, rightEndOfLongestPalindrome = 0;

    for ( int i = 1; i <= NN; ++i )
    {
        if ( rightEndOfLongestPalindrome > i )
                P[i] = min( P[2 * indexOfLongestPalindrome - i], rightEndOfLongestPalindrome - i ); /// we either choose the mirror of i relative to indexOfLongestPalindrome
                                                                                                    /// or we choose to skip some characters because these characters are for sure to be palindromic
        else
                P[i] = 0;

        while ( SS[i - P[i] - 1] == SS[i + P[i] + 1] ) /// we try to extend the palindrome centered at i
                P[i]++;

        if ( P[i] + i > rightEndOfLongestPalindrome ) /// if the palindrome centered at i extends after the one we have already we save the new one
        {
            rightEndOfLongestPalindrome = P[i] + i;
            indexOfLongestPalindrome = i;
        }
    }
}

int main()
{
    cin >> ( S + 1 );

    N = strlen( S + 1 );

    transform();
    Manacher();

    return 0;
}
