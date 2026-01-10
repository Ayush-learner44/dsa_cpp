#include <iostream>
#include <vector>
using namespace std;

int max_profit(vector<int> v)
{
    int count = v.size();
    int maxProfit = -999999, profit = 0, minimum = 9999999;

    for (int i = 0; i < count; i++)
    {
        minimum = min(minimum, v[i]);
        profit = v[i] - minimum;
        maxProfit = max(profit, maxProfit);
    }
    return maxProfit;
}

int main()
{
    vector<int> v = {7, 1, 5, 6, 3, 4};
    cout << max_profit(v) << endl;
}