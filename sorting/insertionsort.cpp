#include <iostream>
#include <vector>

using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void insertionsort(vector<int> &v)
{
    // for (int i = 0; i < v.size(); i++)
    // {
    //     int j = i;
    //     while (j > 0 && v[j] < v[j - 1])
    //     {
    //         swap(v[j], v[j - 1]);
    //         cout << "Run\n";
    //     }
    // }

    // little more optimised way
    for (int i = 0; i < v.size(); i++)
    {
        int key = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > key)
        {
            // shifting
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

int main()
{
    vector<int> v = {7, 6, 5, 4, 3, 2, 1, 67, 789, 32, 45, 324};
    // vector<int> v = {1, 2, 3, 4, 5, 6, 7};
    insertionsort(v);
    for (int i = 0; i < v.size(); i++)
    {
        printf("%d ", v[i]);
    }
}