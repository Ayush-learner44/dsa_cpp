#include <iostream>
#include <string>
#include <cctype> // Required for tolower()
using namespace std;

void isPalindrome(string s, int l, int r)
{

    if (l >= r)
    {
        printf("Palindrome!!");
        return;
    }

    if (tolower(s[l]) != tolower(s[r]))
    {
        printf("Not Palindrome!!");
        return;
    }

    isPalindrome(s, l + 1, r - 1);
}

int main()
{
    string s;
    printf("String?? ");

    getline(cin, s);

    if (s.empty())
    {
        printf("Empty string!");
        return 0;
    }

    isPalindrome(s, 0, s.size() - 1);
    return 0;
}