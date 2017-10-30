#include <iostream>
using std::wcout;
using std::endl;

bool
IsBigEndian()
{
    const int i = 1;
    if ('\x1' == *reinterpret_cast<const char*>(&i))
        return false;
    return true;
}

bool
IsBigEndian_Union()
{
    union
    {
        char    c;
        int     i;
    } u;
    u.i = 1;
    if ('\x1' == u.c)
        return false;
    return true;
}

int
main()
{
    wcout << L"CPU is ";
    if (IsBigEndian())
        wcout << L"big";
    else
        wcout << L"little";
    wcout << L" endian." << endl;
    wcout << L"CPU is ";
    if (IsBigEndian_Union())
        wcout << L"big";
    else
        wcout << L"little";
    wcout << L" endian." << endl;
    return 0;
}