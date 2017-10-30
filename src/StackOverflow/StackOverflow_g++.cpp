// This piece of code could only work when compiled by g++ and don't use -O option, tested version is 4.6.1.
// Compile by command g++ -m64 StackOverflow_g++.cpp -o StackOverflow_g++

#include <cstdlib>
#include <iostream>
using std::wcout;
using std::endl;

// Hacker's code
void
OpenBackdoor()
{
    // Open the back door
    wcout << L"Back door is ready. Welcome!" << endl;
    exit(0);
}

// Service code
void
DefectiveFun(const unsigned char *pRecved, unsigned char *pSent)
{
#define SIZE_LL (sizeof(unsigned long long)) 
    // Process message and generate the response message
    *((unsigned long long*)&pSent[1+0x00]) = 0x0102030405060708;
/*    *((unsigned long long*)&pSent[1+SIZE_LL]) = 0x090A0B0C0D0E0F10;
    *((unsigned long long*)&pSent[1+SIZE_LL*2]) = 0x1112131415161718;
    *((unsigned long long*)&pSent[1+SIZE_LL*3]) = 0x191A1B1C1D1E1F20;
    *((unsigned long long*)&pSent[1+SIZE_LL*4]) = 0x2122232425262728;*/
    *((unsigned long long*)&pSent[1+SIZE_LL]) = (unsigned long long)OpenBackdoor;
    wcout << L"Response sent." << endl;
}

void
ProcessMsgFromNet()
{
    // Get message
    unsigned char   data_recved[1] = {0x00};
    unsigned char   data_sent[1] = {0x000};

    wcout << L"Message received." << endl;
    // Process message
    DefectiveFun(data_recved, data_sent);
    wcout << L"Message processed." << endl;
}

int
main()
{
    ProcessMsgFromNet();
    wcout << L"All done." << endl;
}
