#include <iostream>
#include <vector>

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

    int k = 1, current, maximum = 1;

    for (int i = 0; i < v.size(); i++)
    {
        current = v[i];
        while (i < v.size())
        {
            if (current == v[i])
            {
                i++;
                continue;
            }
            else if ((current + 1) == v[i])
                k++, i++, current++;

            else
            {
                maximum = max(maximum, k);
                k = 1;
                break;
            }
        }
    }

    return maximum;
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
}