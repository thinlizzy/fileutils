#ifndef PATH_H_GUARD_dj2434324
#define PATH_H_GUARD_dj2434324

#include "Filename.h"

namespace fs {

class Path {
	Filename path;
    void addDelim();
public:
	Path() = default;
	Path(Filename const & path);
	Path append(Filename const & subpath) const;
	Path append(Path const & subpath) const;
    Path replaceFilename(Filename const & filename) const;
    Filename asFilename() const;
	operator Filename() const;

    static char const delim;
    static char const otherDelim;
    static Filename normalize(Filename path);
    static Filename changeSeparator(Filename path, char ch);
    static Filename changeSeparator(Filename path, wchar_t ch);
    static bool isDelim(char ch);
    static bool isDelim(wchar_t ch);
};

}

#endif
