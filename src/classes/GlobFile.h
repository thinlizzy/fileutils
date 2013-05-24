#ifndef GLOB_FILE_H_j3432jvncxxx
#define GLOB_FILE_H_j3432jvncxxx

#include <memory>
#include <NativeString.h>

namespace fs {
    
class GlobImpl;

class GlobFile {
    friend class GlobIterator;
    std::unique_ptr<GlobImpl> impl;
    GlobFile(GlobImpl * impl);
public:
    GlobFile();
    ~GlobFile();
    die::NativeString filename() const;
    bool isDirectory() const;
    bool isSpecialDirectory() const;
};

}

#endif
