#include <iostream>
using namespace std;

void pattern(int rows)
{
    int spaces = 0;
    char ch = 'A';

    for (int i = 1; i <= rows; i++)
    {
        spaces = rows - i;
        ch = 'A';
        int j = i;

        while (spaces--)
        {
            cout << " ";
        }
        while (j--)
        {
            cout << ch;
            ch = ch + 1;
        }
        j = i - 1;
        ch = ch - 1;
        while (j--)
        {
            ch = ch - 1;
            cout << ch;
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