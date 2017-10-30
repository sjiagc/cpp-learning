#include <iostream>

using std::wcout;
using std::endl;

template<typename T>
class B
{
};

template<typename T>
class S: public B<T>
{
};

class S1: public B<int>
{
};

int
main()
{
    S<int>  s;
    S1      s1;
    B<int>  *pb = &s;
    pb = &s1;
//    B<float>    *pbfl = &s; // Could not be compiled
}
