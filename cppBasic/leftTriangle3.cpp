#include <iostream>
using namespace std;

void pattern(int rows)
{

    for (int i = 1; i <= rows; i++)
    {
        char ch = 'A' + i - 1;

        int j = i;

        while (j--)
        {
            cout << ch << " ";
            ch = ch;
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