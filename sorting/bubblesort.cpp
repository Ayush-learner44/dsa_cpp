#include <iostream>
#include <vector>

using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void bubblesort(vector<int> &v)
{
    int didswap = 0;
    for (int i = 0; i < v.size() - 1; i++)
    {

        for (int j = 0; j < v.size() - i - 1; j++)
        {
            if (v[j] > v[j + 1])
            {
                swap(v[j], v[j + 1]);
                didswap = 1;
            }
        }
        if (!didswap)
            return;
    }
}

int main()
{
    vector<int> v = {7, 6, 5, 4, 3, 2, 1, 67, 789, 32, 45, 324};
    bubblesort(v);
    for (int i = 0; i < v.size(); i++)
    {
        printf("%d ", v[i]);
    }
}