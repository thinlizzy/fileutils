#ifndef FILENAME_H_FILEUTILS_DIEGO_2015_07_28
#define FILENAME_H_FILEUTILS_DIEGO_2015_07_28

#include <string>
#include <iostream>

namespace fs {

class Filename {
public:
    Filename();
    Filename(char const * str);
    Filename(std::string const & str);
    Filename(wchar_t const * str);
    Filename(std::wstring const & str);
    ~Filename();

    Filename(Filename const & other);
    Filename(Filename && other);
    Filename & operator=(Filename other);
    void swap(Filename & other);

    bool empty() const;
    Filename & operator+=(Filename const & other);
    bool operator==(Filename const & other) const;
    bool operator!=(Filename const & other) const;

    std::string toUTF8() const;
    std::wstring toUTF16() const;

    // internal, do not use!
    union {
        std::string str;
        std::wstring wstr;
    };
};

inline Filename operator+(Filename a, Filename const & b) { return a+=b; }
bool operator<(Filename const & a, Filename const & b);

inline std::ostream & operator<<(std::ostream & os, Filename const & str) { return os << str.toUTF8(); }
inline std::wostream & operator<<(std::wostream & os, Filename const & str) { return os << str.toUTF16(); }

}

#endif
