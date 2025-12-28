#include <iostream>
using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void reverse(int arr[], int l, int r)
{
    if (l > r)
        return;
    swap(arr[l], arr[r]);
    reverse(arr, ++l, --r);
}

void reverse_again(int arr[], int i, int size)
{
    if (i >= size / 2)
        return;
    swap(arr[i], arr[size - i - 1]);
    reverse_again(arr, i + 1, size);
}
int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    reverse(arr, 0, 4);
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << " ";
    }
    reverse_again(arr, 0, 5);
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << " ";
    }
}