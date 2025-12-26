#include <iostream>
using namespace std;

void pattern(int rows)
{
    for (int i = 0; i < rows; i++)
    {
        int stars = (1 + 2 * i);
        int spaces = rows - i - 1;
        while (spaces--)
        {
            cout << "  ";
        }
        while (stars--)
        {
            cout << "* ";
        }

        cout << endl;
    }
}

void invertedpattern(int rows)
{
    for (int i = rows; i > 0; i--)
    {
        int stars = (2 * i) - 1;
        int spaces = rows - i;
        while (spaces--)
        {
            cout << "  ";
        }
        while (stars--)
        {
            cout << "* ";
        }

        cout << endl;
    }
}

void diamond(int rows)
{
    pattern(rows);
    invertedpattern(rows);
}
int main()
{
    int n;
    cout << "Enter the value of rows: ";
    cin >> n;
    diamond(n);
}