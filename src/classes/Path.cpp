#include "Path.h"
#include "../functions/functions.h"

namespace fs {

Path::Path(die::NativeString const & path):
    path(normalize(path))
{
}

Path Path::append(die::NativeString const & subpath) const
{
    Path result(*this);
    if( subpath.empty() ) return result;
        
    if( ! result.path.empty() ) {
        result.addDelim();
    }
    result.path += normalize(subpath);
    return result;
}

Path Path::append(Path const & subpath) const
{
    return append(subpath.path);
}

Path Path::replaceFilename(die::NativeString const & filename) const
{
    return Path(extractPath(path)).append(filename);
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