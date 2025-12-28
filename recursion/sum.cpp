#include <iostream>
using namespace std;

int sum_param(int n, int sum)
{
    if (n == 0)
        return sum;
    return sum_param(n - 1, sum + n);
}

int sum_func(int n)
{
    if (n == 0)
        return 0;
    return n + sum_func(n - 1);
}

int main()
{
    int n;
    cout << "Number??";
    cin >> n;
    cout << sum_param(n, 0) << " ";
    cout << sum_func(n) << " ";
}