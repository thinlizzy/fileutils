#include "UTF8Converters.h"
#include <Windows.h>
#include <iostream>

std::wstring utf8_to_ws(char const text[])
{
    int total = MultiByteToWideChar(CP_UTF8,0,text,-1,0,0);
    std::wstring converted(total,L'\0');
    if( MultiByteToWideChar(CP_UTF8,0,text,-1,&converted[0],total) == 0 ) {
        std::cerr << "MultiByteToWideChar error " << GetLastError() << std::endl;
    }
    converted.pop_back();
    return converted;
}

std::string wc_to_utf8(wchar_t const text[])
{
    int total = WideCharToMultiByte(CP_UTF8,0,text,-1,0,0,0,0);
    std::string converted(total,'\0');
    if( WideCharToMultiByte(CP_UTF8,0,text,-1,&converted[0],total,0,0) == 0 ) {
        std::cerr << "WideCharToMultiByte error " << GetLastError() << std::endl;
    }
    converted.pop_back();
    return converted;
}

