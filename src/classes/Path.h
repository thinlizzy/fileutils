#ifndef PATH_H_GUARD_dj2434324
#define PATH_H_GUARD_dj2434324

#include <NativeString.h>

namespace fs {

class Path {
	die::NativeString path;
    void addDelim();
public:
	Path() = default;
	Path(die::NativeString const & path);
	Path append(die::NativeString const & subpath) const;
	Path append(Path const & subpath) const;
    Path replaceFilename(die::NativeString const & filename) const;
	die::NativeString getPath() const;
	operator die::NativeString() const;

    static char const delim;
    static char const otherDelim;
    static die::NativeString normalize(die::NativeString path);    
    static bool isDelim(char ch);
    static bool isDelim(wchar_t ch);
};

}

#endif
