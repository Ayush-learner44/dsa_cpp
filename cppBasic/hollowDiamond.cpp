#include <iostream>
using namespace std;

void top(int rows)
{
    int stars, spaces;
    for (int i = rows; i > 0; i--)
    {
        stars = i;
        spaces = rows - stars;
        while (stars--)
        {
            cout << "* ";
        }
        while (spaces--)
        {
            cout << "  ";
        }

        stars = i;
        spaces = rows - stars;
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
void bottom(int rows)
{
    int stars, spaces;
    for (int i = rows; i > 0; i--)
    {
        spaces = i - 1;
        stars = rows - spaces;
        while (stars--)
        {
            cout << "* ";
        }
        while (spaces--)
        {
            cout << "  ";
        }
        spaces = i - 1;
        stars = rows - spaces;
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
    top(rows);
    bottom(rows);
}
int main()
{
    int n;
    cout << "Enter the value of rows: ";
    cin >> n;
    diamond(n);
}