#include <iostream>
using namespace std;

void square(int rows)
{
    if ((rows % 2) == 1)
        rows = rows - 1;

    int spaces = rows - 2;

    for (int i = 1; i <= rows; i++)
    {
        if (i == 1 or i == rows)
        {
            for (int j = 0; j < rows; j++)
            {
                cout << "* ";
            }
            cout << endl;
            continue;
        }
        spaces = rows - 2;
        cout << "* ";
        while (spaces--)
        {
            cout << "  ";
        }
        cout << "* ";
        cout << endl;
    }
}

int main()
{
    int n;
    cout << "Rows?";
    cin >> n;
    square(n);
}