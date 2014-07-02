#include "../classes/GlobIterator.h"
#include <Windows.h>
#include <cstring>
#include <string>
#include <iostream>

namespace fs {

class GlobImpl {
    HANDLE handle;
public:
    DWORD lastError;
    WIN32_FIND_DATAW data;

    GlobImpl(wchar_t const pathUTF16[]):
        lastError(0)
    {
        handle = FindFirstFileW(pathUTF16,&data);
        if( invalid() ) {
            lastError = GetLastError();
        }
    }

    ~GlobImpl() { FindClose(handle); }

    bool invalid() const { return handle == INVALID_HANDLE_VALUE; }

    bool noMoreFiles() const { return lastError == ERROR_NO_MORE_FILES; } 
    
    bool hasError() const { return invalid() || lastError != 0; }

    bool findNext() {
        auto res = FindNextFileW(handle,&data);
        if( ! res ) {
            lastError = GetLastError();
        }
        return res;
    }
};

// File

GlobFile::GlobFile(GlobImpl * impl):
    impl(impl)
{}

GlobFile::GlobFile()
{}

GlobFile::~GlobFile()
{}

GlobFile::GlobFile(GlobFile && other):
    impl(std::move(other.impl))
{}

GlobFile & GlobFile::operator=(GlobFile && other)
{
    impl = std::move(other.impl);
    return *this;
}

die::NativeString GlobFile::filename() const
{
    return impl->data.cFileName;
}

size_t GlobFile::filesize() const
{
    return (impl->data.nFileSizeHigh * (MAXDWORD+1)) + impl->data.nFileSizeLow;
}

bool GlobFile::isDirectory() const
{
    return impl->data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
}

bool GlobFile::isSpecialDirectory() const
{
    return wcscmp(impl->data.cFileName,L".") == 0 ||
    wcscmp(impl->data.cFileName,L"..") == 0;
}

// Iterator

GlobIterator::GlobIterator(die::NativeString const & path):
    file(new GlobImpl(path.wstr.c_str()))
{}

GlobFile & GlobIterator::operator*()
{
    return file;
}

GlobFile const & GlobIterator::operator*() const
{
    return file;
}

GlobFile * GlobIterator::operator->()
{
    return &file;
}

GlobFile const * GlobIterator::operator->() const
{
    return &file;
}

GlobIterator & GlobIterator::operator++()
{
    file.impl->findNext();
    
    return *this;
}

bool GlobIterator::operator==(GlobIterator const & it) const
{
    // they are equal only at the sentinel value
    return (! file.impl || file.impl->hasError() ) && ! it.file.impl;           
}

bool GlobIterator::operator!=(GlobIterator const & it) const
{
    return ! operator==(it);
}

Status GlobIterator::getStatus()
{
    if( file.impl->invalid() ) return failed;
    if( file.impl->noMoreFiles() ) return ignored;
    return ok;
}

}
