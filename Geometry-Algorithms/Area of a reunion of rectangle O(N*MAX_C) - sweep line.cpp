#include <bits/stdc++.h>

using namespace std;

/**
    Area of union of rectangles
    -sweep line technique
    -vector used for marks

    Time: O(N*MAX_C)
    Memory: O(N+MAX_C)
**/

const int MAX_COORD = 30000;
const int Nmax = 10000;

struct Event
{
    int x;
    int y1, y2;
    bool type; /// 0/1 for insert/erase

    bool operator < (const Event& E) const
    {
        return x < E.x;
    }
};

int marked[MAX_COORD + 1];
Event events[2 * Nmax + 1];

int N;
int nrEvents;

void insertEvent(int y1, int y2)
{
    for (int i = y1; i < y2; ++i)
        marked[i]++;
}

void eraseEvent(int y1, int y2)
{
    for (int i = y1; i < y2; ++i)
        marked[i]--;
}

int getHeight()
{
    int sum = 0;

    for (int i = 0; i <= MAX_COORD; ++i)
        if (marked[i] > 0)
            sum++;

    return sum;
}

int main()
{
    ///freopen("data.in", "r", stdin);

    scanf("%d ", &N);

    for (int i = 0; i < N; ++i)
    {
        int x1, y1, x2, y2;
        /// A rectangle is defined by it's bottom left and top right coordinates
        scanf("%d %d %d %d ", &x1, &y1, &x2, &y2);

        events[++nrEvents] = {x1, y1, y2, 0};
        events[++nrEvents] = {x2, y1, y2, 1};
    }

    sort(events + 1, events + nrEvents + 1);

    int totalArea = 0;

    for (int i = 1; i <= nrEvents; ++i)
    {
        if (i != 1) /// has a previous event
            totalArea += (events[i].x - events[i - 1].x) * getHeight();

        if (events[i].type == 0)
            insertEvent(events[i].y1, events[i].y2);

        if (events[i].type == 1)
            eraseEvent(events[i].y1, events[i].y2);
    }

    cout << totalArea << "\n";

    return 0;
}
