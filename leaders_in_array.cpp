// Everything on the right of it should be smaller than the number

#include <iostream>
#include <vector>

using namespace std;

void leaders_brute(vector<int> v)
{
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        int leader = v[i];

        for (int j = i + 1; j < n; j++)
        {
            if (v[j] > leader)
            {
                leader = -1;
                break;
            }
        }
        if (leader == -1)
            continue;
        else
            cout << leader << " ";
    }
}

void leader_optimal(vector<int> v)
{
    int count = v.size();
    int leader = -99999;
    for (int i = count - 1; i >= 0; i--)
    {
        if (v[i] > leader)
        {
            leader = v[i];
            cout << leader << " ";
        }
    }
}

int main()
{
    vector<int> v = {10, 22, 12, 3, 0, 6};
    leaders_brute(v);
    cout << endl;
    leader_optimal(v);
}