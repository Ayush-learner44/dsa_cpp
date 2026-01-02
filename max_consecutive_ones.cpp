#include <iostream>
#include <vector>

using namespace std;

int countOnes(vector<int> v)
{
    int max = 0;
    int count = 0;

    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == 1)
            count++;
        else
        {
            count > max ? max = count : max;
            count = 0;
        }
    }

    return max;
}

int main()
{
    vector<int> v = {1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1};
    cout << countOnes(v);
}