#include <iostream>
using namespace std;

void pattern(int rows)
{
    int col = rows * 2;

    for (int i = 1; i <= rows; i++)
    {
        int k = 1;
        int spaces = col - (i * 2);
        int j = i;

        while (j--)
        {
            cout << k++;
        }
        while (spaces--)
        {
            cout << " ";
        }

        while (--k)
        {
            cout << k;
        }

        cout << endl;
    }
}

int main()
{
    int n;
    cout << "Enter the value of rows: ";
    cin >> n;
    pattern(n);
}