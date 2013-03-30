#ifndef GLOBITERATOR_H_GUARD_j3243fdsfs
#define GLOBITERATOR_H_GUARD_j3243fdsfs

#include <string>
#include <iterator>
#include "Status.h"
#include "GlobFile.h"

namespace fs {

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
