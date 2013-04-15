#ifndef PATH_H_GUARD_dj2434324
#define PATH_H_GUARD_dj2434324

#include "NativeString.h"

namespace fs {

class Path {
	NativeString path;
    void addDelim();
public:
	Path() = default;
	Path(NativeString const & path);
	Path append(NativeString const & subpath) const;
	Path append(Path const & subpath) const;
	NativeString getPath() const;
	operator NativeString() const;

    static char const delim;
    static char const otherDelim;
    static NativeString normalize(NativeString path);    
    static bool isDelim(char ch);
    static bool isDelim(wchar_t ch);
};

}

#endif
