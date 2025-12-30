#include <iostream>
#include <vector>

using namespace std;

int secondLargest(vector<int> v)
{
    int size = v.size();

    int first = v[0], second = -1;

    for (int i = 1; i < size; i++)
    {
        if (v[i] > first)
        {
            second = first;
            first = v[i];
        }
        else if (v[i] < first and v[i] > second)
            second = v[i];
    }

    return second;
}

int secondSmallest(vector<int> v)
{
    int first = INT_MAX;
    int second = INT_MAX;

    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] < first)
        {
            second = first;
            first = v[i];
        }
        else if (v[i] > first and v[i] < second)
        {
            second = v[i];
        }
    }

    return second;
}
int main()
{
    vector<int> v = {1, 5, 3, 5, 7, 8, 4};
    cout << secondLargest(v) << endl;
    cout << secondSmallest(v) << endl;
}