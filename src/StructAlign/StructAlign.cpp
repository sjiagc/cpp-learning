#include <iostream>

using std::wcout;
using std::endl;

#define OFFSET(t, m)    ((unsigned long)&(((t*)0)->m))
#define ALGIN(t)    ((unsigned long)&(((t*)0)[1]))

struct A
{
    char    a;
    double  b;
    char    c;
    int     d;
    char    e;
    float   f;
    char    g;
    short   h;
};

#pragma pack(push, 1)
struct A_1
{
    char    a;
    double  b;
    char    c;
    int     d;
    char    e;
    float   f;
    char    g;
    short   h;
};
#pragma pack(pop)

int
main()
{
    wcout << L"Offset of default alignment" << endl;
    wcout << std::hex;
    wcout << L"A::a " << OFFSET(A, a) << endl;
    wcout << L"A::b " << OFFSET(A, b) << endl;
    wcout << L"A::c " << OFFSET(A, c) << endl;
    wcout << L"A::d " << OFFSET(A, d) << endl;
    wcout << L"A::e " << OFFSET(A, e) << endl;
    wcout << L"A::f " << OFFSET(A, f) << endl;
    wcout << L"A::g " << OFFSET(A, g) << endl;
    wcout << L"A::h " << OFFSET(A, h) << endl;
    wcout << L"struct A " << ALGIN(A) << endl;
    
    wcout << L"Offset of 1 byte alignment" << endl;
    wcout << L"A_1::a " << OFFSET(A_1, a) << endl;
    wcout << L"A_1::b " << OFFSET(A_1, b) << endl;
    wcout << L"A_1::c " << OFFSET(A_1, c) << endl;
    wcout << L"A_1::d " << OFFSET(A_1, d) << endl;
    wcout << L"A_1::e " << OFFSET(A_1, e) << endl;
    wcout << L"A_1::f " << OFFSET(A_1, f) << endl;
    wcout << L"A_1::g " << OFFSET(A_1, g) << endl;
    wcout << L"A_1::h " << OFFSET(A_1, h) << endl;
    wcout << L"struct A_1 " << ALGIN(A_1) << endl;

    ;
}
