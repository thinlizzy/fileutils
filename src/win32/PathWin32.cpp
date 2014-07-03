#include "../classes/Path.h"
#include <algorithm>

namespace fs {

char const Path::delim = '\\';
char const Path::otherDelim = '/';

wchar_t const wdelim = wchar_t(Path::delim);
wchar_t const wotherDelim = wchar_t(Path::otherDelim);

die::NativeString Path::normalize(die::NativeString path)
{
    std::replace(path.wstr.begin(),path.wstr.end(),wotherDelim,wdelim);
    if( ! path.empty() && path.wstr.back() == wdelim ) {
        path.wstr.erase(std::prev(path.wstr.end()));
    }
    if( ! path.empty() && path.wstr.front() == wdelim ) {
        path.wstr.erase(path.wstr.begin());
    }
    return path;
}

die::NativeString Path::changeSeparator(die::NativeString path, char ch)
{
    return changeSeparator(path,wchar_t(ch));
}

die::NativeString Path::changeSeparator(die::NativeString path, wchar_t ch)
{
    std::replace(path.wstr.begin(),path.wstr.end(),wdelim,ch);
    return path;
}


void Path::addDelim()
{
    path.wstr += wdelim;
}

}