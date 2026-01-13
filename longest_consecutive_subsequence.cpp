#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int lcs(vector<int> v)
{
    int count = v.size();
    int maximum = 1;
    for (int i = 0; i < count; i++)
    {
        int current = v[i], current_max = 1;
        for (int j = 0; j < count; j++)
        {
            if (j == i)
                continue;
            if (v[j] == current + 1)
                current_max++, current++, j = 0;
        }
        maximum = max(current_max, maximum);
    }
    return maximum;
}

int lcs_better(vector<int> v)
{
    sort(v.begin(), v.end());

    int max_streak = 1, streak = 1, last_smaller = v[0];

    for (int i = 1; i < v.size(); i++)
    {
        if (last_smaller + 1 == v[i])
        {
            streak++;
            last_smaller = v[i];
        }
        else if (last_smaller != v[i])
        {
            max_streak = max(max_streak, streak);
            last_smaller = v[i];
            streak = 1;
        }
    }

    return max(max_streak, streak);
}

// optimal
int lcs_optimal(vector<int> v)
{
    int max_streak = 1, streak = 1;
    unordered_set<int> st(v.begin(), v.end());

    for (auto i : st)
    {
        if (st.find(i - 1) == st.end())
        {
            int x = i;
            while (st.find(x + 1) != st.end())
            {
                streak++, x++;
            }
            max_streak = max(max_streak, streak);
            streak = 1;
        }
    }
    return max_streak;
}

int main()
{
    // vector<int> v = {102, 4, 100, 1, 101, 3, 2, 1, 1};
    vector<int> v = {
        102,
        4,
        100,
        1,
        101,
        3,
        2,
        1,
        1,
        2,
        2,
        2,
        3,
        3,
        2,
        3,
        2,
        3,
        1,
        1,
        2,
        3,
        1,
        2,
        4,
        2,
        3,
        5,
        6,
        6,
        6,
    };
    cout << lcs(v) << endl;
    cout << lcs_better(v) << endl;
    cout << lcs_optimal(v) << endl;
}