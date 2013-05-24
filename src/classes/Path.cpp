#include "Path.h"

namespace fs {

Path::Path(die::NativeString const & path):
    path(normalize(path))
{
}

Path Path::append(die::NativeString const & subpath) const
{
    Path result(*this);
    result.addDelim();
    result.path += normalize(subpath);
    return result;
}

Path Path::append(Path const & subpath) const
{
    return append(subpath.path);
}

Path::operator die::NativeString() const
{
    return getPath();
}

die::NativeString Path::getPath() const
{
    return path;
}

bool Path::isDelim(char ch)
{
    return ch == delim || ch == otherDelim;
}

bool Path::isDelim(wchar_t ch)
{
    return ch == delim || ch == otherDelim;
}

}