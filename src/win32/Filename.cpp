#include "../classes/Filename.h"
#include <iostream>
#include <windows.h>

namespace {

std::string ws_to_utf8(std::wstring const & wstr)
{
    int total = WideCharToMultiByte(CP_UTF8,0,wstr.c_str(),wstr.size(),0,0,0,0);
    std::string converted(total,'\0');
    WideCharToMultiByte(CP_UTF8,0,wstr.c_str(),wstr.size(),&converted[0],total,0,0);
    return converted;
}

std::wstring utf8_to_ws(char const * text, int size)
{
    if( size == 0 ) return std::wstring();

//    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//    blah = converter.from_bytes(text);
    int total = MultiByteToWideChar(CP_UTF8,0,text,size,0,0);
    std::wstring converted(total,L'\0');
    if( MultiByteToWideChar(CP_UTF8,0,text,size,&converted[0],total) == 0 ) {
#ifdef NDEBUG
        std::cerr << "error converting string" << std::endl;
#else
        std::cerr << "error converting [" << text << "]  size " << size << std::endl;
#endif
    }
    return converted;
}

std::wstring utf8_to_ws(char const * text)
{
    auto converted = utf8_to_ws(text,-1);
    converted.pop_back(); // remove the null terminated char
    return converted;
}

std::wstring utf8_to_ws(std::string const & text)
{
    if( text.empty() ) return std::wstring();
    return utf8_to_ws(text.c_str(),text.size());
}

}

namespace fs {

Filename::Filename():
    wstr()
{}

Filename::Filename(std::string const & str):
    wstr(utf8_to_ws(str))
{}

Filename::Filename(char const * str):
    wstr(utf8_to_ws(str))
{}

Filename::Filename(std::wstring const & str):
    wstr(str)
{}

Filename::Filename(wchar_t const * str):
    wstr(str)
{}

Filename::~Filename()
{
    using std::wstring;
    wstr.~wstring();
}

Filename::Filename(Filename const & other):
    wstr(other.wstr)
{}

Filename::Filename(Filename && other):
    wstr(std::move(other.wstr))
{}

Filename & Filename::operator=(Filename other)
{
    swap(other);
    return *this;
}

void Filename::swap(Filename & other)
{
	wstr.swap(other.wstr);
}

std::string Filename::toUTF8() const
{
    return ws_to_utf8(wstr);
}

std::wstring Filename::toUTF16() const
{
    return wstr;
}

bool Filename::empty() const
{
    return wstr.empty();
}

Filename & Filename::operator+=(Filename const & other)
{
    wstr += other.wstr;
    return *this;
}

bool Filename::operator==(Filename const & other) const
{
    return wstr == other.wstr;
}

bool Filename::operator!=(Filename const & other) const
{
    return wstr != other.wstr;
}

bool operator<(Filename const & a, Filename const & b)
{
    return a.wstr < b.wstr;
}


}
