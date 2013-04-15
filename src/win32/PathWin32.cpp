#include "../classes/Path.h"

namespace fs {

char const Path::delim = '\\';
char const Path::otherDelim = '/';

char const wdelim = wchar_t(Path::delim);
char const wotherDelim = wchar_t(Path::otherDelim);

NativeString Path::normalize(NativeString path)
{
    for( wchar_t & ch : path.wstr ) {
        if( ch == wotherDelim ) ch = wdelim;
    }
    if( ! path.empty() && path.wstr.back() == wdelim ) {
        path.wstr.erase(std::prev(path.wstr.end()));
    }
    if( ! path.empty() && path.wstr.front() == wdelim ) {
        path.wstr.erase(path.wstr.begin());
    }
    return path;
}

void Path::addDelim()
{
    path.wstr += wdelim;
}

}