// arrange the +ve on odd positions and -ves on the even positions..that's it...but this time the number of -ves and +ves are not equal and therefore keep the rest numbers at the end.

#include <iostream>
#include <vector>

using namespace std;

// only one solution and that is the brute one ok..

void rearrange(vector<int> &v)
{
    vector<int> positive, negative;

    int n = v.size();

    for (int i = 0; i < n; i++)
    {
        if (v[i] >= 0)
            positive.emplace_back(v[i]);
        else
            negative.emplace_back(v[i]);
    }

    int s1 = positive.size(), s2 = negative.size();

    if (s1 == s2)
    {
        for (int i = 0; i < n / 2; i++)
        {
            v[2 * i] = positive[i];
            v[2 * i + 1] = negative[i];
        }
    }
    else if (s1 > s2)
    {
        int i = 0;

        for (; i < s2; i++)
        {
            v[2 * i] = positive[i];
            v[2 * i + 1] = negative[i];
        }

        i = 2 * i;
        int k = i;

        while (k < s1 and i < n)
        {
            v[i++] = positive[k++];
        }
    }
    else
    {
        int i = 0;

        for (; i < s1; i++)
        {
            v[2 * i] = positive[i];
            v[2 * i + 1] = negative[i];
        }

        i = 2 * i + 1;
        int k = i;

        while (k < s2 and i < n)
        {
            v[i++] = positive[k++];
        }
    }
}

int main()
{
    // vector<int> v = {-1, 2, 3, 4, -6, -7, -8, 0, -3, -4, -8};
    vector<int> v = {-1, 2, 3, 4, -6, -7, -8, 0, 3, 4, 8};
    rearrange(v);
    for (int i : v)
        cout << i << " ";
}