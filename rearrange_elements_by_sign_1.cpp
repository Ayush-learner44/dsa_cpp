// the number of -ves and +ves are equal....now keep the +ve at odd and the -ves at even

#include <iostream>
#include <vector>

using namespace std;

void rearrage_brute(vector<int> &v)
{
    int n = v.size();
    vector<int> positive;
    vector<int> negative;

    for (int i = 0; i < n; i++)
    {
        if (v[i] >= 0)
            positive.emplace_back(v[i]);
        else
            negative.emplace_back(v[i]);
    }

    for (int i = 0; i < n / 2; i++)
    {
        v[2 * i] = positive[i];
        v[2 * i + 1] = negative[i];
    }
}

void rearrange_optimal(vector<int> v)
{
    int n = v.size();
    vector<int> ans(n, 0);
    int positive = 0, negative = 1;
    for (int i = 0; i < n; i++)
    {
        if (v[i] >= 0)
        {
            ans[positive] = v[i];
            positive += 2;
        }
        else
        {
            ans[negative] = v[i];
            negative += 2;
        }
    }

    for (int i : ans)
        cout << i << " ";
}

int main()
{
    vector<int> v = {-1, 2, 3, 4, -6, -7, -8, 0};
    rearrange_optimal(v);
    cout << endl;
    rearrage_brute(v);
    for (int i : v)
        cout << i << " ";
}