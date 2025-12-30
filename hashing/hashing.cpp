#include <iostream>
#include <vector>
using namespace std;

void frequency(vector<int> v)
{
    if (v.empty())
        return;

    int maxVal = *max_element(v.begin(), v.end());

    vector<int> temp(maxVal + 1, 0);
    for (auto i : v)
    {
        temp[i]++;
    }
    int index = 0;

    for (int i = 0; i < temp.size(); i++)
    {
        if (temp[i] > 0)
            cout << i << ":" << temp[i];
        cout << endl;
        /* code */
    }
}
int main()
{
    vector<int> v = {
        1,
        2,
        4,
        5,
        6,
        8,
        9,
        3,
        4,
        4,
        4,
        5,
        5,
        7,
        2,
        1,
        3,
        5,
        6,
        7,
        9,
        9,
        4,
        3,
        3,
        6,
        7,
        3,
    };
    frequency(v);
}