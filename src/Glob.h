#ifndef GLOB_H_GUARD_j3243fdsfs
#define GLOB_H_GUARD_j3243fdsfs

#include "common.h"
#include <string>
#include <memory>
#include <iterator>

namespace fs {

class GlobImpl;

class GlobFile {
    friend class GlobIterator;
    std::unique_ptr<GlobImpl> impl;
    GlobFile(GlobImpl * impl);
public:
    GlobFile();
    ~GlobFile();
    char const * filename() const;
    bool isDirectory() const;
    bool isSpecialDirectory() const;
};

class GlobIterator: public std::iterator<std::forward_iterator_tag,GlobFile> {
    GlobFile file;
public:
    GlobIterator() = default;
    explicit GlobIterator(char const path[]);
    explicit GlobIterator(std::string const & path);

    GlobFile & operator*();
    GlobFile const & operator*() const;
    GlobFile * operator->();
    GlobFile const * operator->() const;
    GlobIterator & operator++();
    bool operator==(GlobIterator const & it) const;
    bool operator!=(GlobIterator const & it) const;
    Status getStatus();
};

}

#endif
