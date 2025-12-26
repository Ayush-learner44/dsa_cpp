#include <iostream>
using namespace std;

void top(int rows)
{
    int spaces, k = rows, temp = rows;

    for (int i = 0; i < rows; i++)
    {
        spaces = i;
        k = rows - i;
        temp = rows;
        for (int j = 0; j < spaces; j++)
        {
            cout << (temp--) << " ";
        }

        for (int j = 0; j < rows - spaces; j++)
        {
            cout << k << " ";
        }

        // topright

        for (int j = 1; j < rows - spaces; j++)
        {
            cout << k << " ";
        }

        temp = rows - i + 1;
        for (int j = 0; j < spaces; j++)
        {
            cout << (temp++) << " ";
        }

        cout << endl;
    }
}
void bottom(int rows)
{
    int spaces, k = rows, temp = rows;

    for (int i = rows - 1; i > 0; i--)
    {
        spaces = i - 1;
        k = rows - spaces;
        temp = rows;

        for (int j = 0; j < spaces; j++)
        {
            cout << (temp--) << " ";
        }

        for (int j = 0; j < rows - spaces; j++)
        {
            cout << k << " ";
        }

        // topright

        for (int j = 1; j < rows - spaces; j++)
        {
            cout << k << " ";
        }

        temp = rows - i + 2;
        for (int j = 0; j < spaces; j++)
        {
            cout << (temp++) << " ";
        }

        cout << endl;
    }
}

void square(int rows)
{
    top(rows);
    bottom(rows);
}

int main()
{
    int n;
    cout << "Rows? ";
    cin >> n;
    square(n);
}