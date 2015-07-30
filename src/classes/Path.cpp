#include "Path.h"
#include "../functions/functions.h"

namespace fs {

Path::Path(Filename const & path):
    path(normalize(path))
{
}

Path Path::append(Filename const & subpath) const
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

Path Path::replaceFilename(Filename const & filename) const
{
    return Path(extractPath(path)).append(filename);
}

Path::operator Filename() const
{
    return asFilename();
}

Filename Path::asFilename() const
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
