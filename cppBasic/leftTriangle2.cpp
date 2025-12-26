#include <iostream>
using namespace std;

void pattern(int rows)
{

    char ch = 'A';
    for (int i = 1; i <= rows; i++)
    {

        int j = i;

        while (j--)
        {
            cout << ch << " ";
            ch = ch + 1;
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