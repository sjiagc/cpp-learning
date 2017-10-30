// This piece of code could only work when compiled by vs2012 in debug mode for Win32 platform
// The debugger will catch the stack overflow signal, just ignore it, then you will see the something intereting happen.

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
    int iOffset = 0;
    // Process message and generate the response message
    *((unsigned int*)&pSent[1+iOffset]) = 0x01020304; iOffset += 0x04;
#ifdef _DEBUG
    *((unsigned int*)&pSent[1+iOffset]) = 0x05060708; iOffset += 0x04;
    *((unsigned int*)&pSent[1+iOffset]) = 0x090A0B0C; iOffset += 0x04;
    *((unsigned int*)&pSent[1+iOffset]) = 0x0D0E0F10; iOffset += 0x04;
    *((unsigned int*)&pSent[1+iOffset]) = 0x11121314; iOffset += 0x04;
#endif
    *((unsigned int*)&pSent[1+iOffset]) = (unsigned int)OpenBackdoor;
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
