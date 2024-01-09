#include <bits/stdc++.h>

using namespace std;

template <const size_t MAX_SIZE>
class DoubleHashing
{
private:

    static const int NIL = -1;
    static const int DELETED = -2;

    int table[MAX_SIZE];

    ///--------------------------------------------------
    size_t h1(const int key) const
    {
        return (1U * key) * 2654435761;
    }

    size_t h2(const int key) const
    {
        return key % 666013;
    }
    ///--------------------------------------------------

    inline bool check(const size_t pos, const int key) const
    {
        return table[pos] != NIL && table[pos] != key;
    }

    int supposedPosition(const int key) const
    {
        size_t pos = 0;

        while (check((h1(key) + pos * h2(key)) % MAX_SIZE, key) == true)
            pos++;

        return (h1(key) + pos * h2(key)) % MAX_SIZE;
    }

public:

    DoubleHashing()
    {
        for (int i = 0; i < MAX_SIZE; ++i)
            table[i] = NIL;
    }

    void insert(const int key)
    {
        table[supposedPosition(key)] = key;
    }

    bool find(const int key)
    {
        return table[supposedPosition(key)] == key;
    }

    void erase(const int key)
    {
        int pos = supposedPosition(key);

        if (table[pos] == key)
            table[pos] = DELETED;
    }
};

int main()
{
    return 0;
}
