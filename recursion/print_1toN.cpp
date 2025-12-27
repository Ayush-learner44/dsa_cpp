#include <iostream>
using namespace std;

// void series(int n, int current = 1)
// {
//     if (current > n)
//         return;
//     cout << current++ << " ";
//     series(n, current);
// }
void series(int n)
{
    if (1 > n)
        return;
    series(n - 1);
    cout << n << " ";
}

void reverse(int n, int m)
{
    if (n < 1)
        return;
    cout << n-- << " ";
    reverse(n, m);
}

int main()
{
    int n;
    cout << "Number? ";
    cin >> n;
    series(n);
    reverse(n, n);
}