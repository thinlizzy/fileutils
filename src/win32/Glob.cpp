#include "../classes/GlobIterator.h"
#include <Windows.h>
#include <cstring>

namespace fs {

class GlobImpl {
	HANDLE handle;
public:
	DWORD lastError;
	WIN32_FIND_DATAA data;

	GlobImpl(char const path[]):
		lastError(0)
	{
		handle = FindFirstFileA(path,&data);
		if( invalid() ) {
			lastError = GetLastError();
		}
	}

	~GlobImpl() { FindClose(handle); }

	bool invalid() { return handle == INVALID_HANDLE_VALUE; }

	bool noMoreFiles() { return lastError == ERROR_NO_MORE_FILES; } 

	bool findNext() {
		auto res = FindNextFileA(handle,&data);
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

char const * GlobFile::filename() const
{
	return impl->data.cFileName;
}

bool GlobFile::isDirectory() const
{
    return impl->data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
}

bool GlobFile::isSpecialDirectory() const
{
	return std::strcmp(impl->data.cFileName,".") == 0 ||
        std::strcmp(impl->data.cFileName,"..") == 0;
}

// Iterator

GlobIterator::GlobIterator(char const path[]):
    file(new GlobImpl(path))
{}

GlobIterator::GlobIterator(std::string const & path):
    file(new GlobImpl(path.c_str()))
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
	if( ! file.impl->findNext() ) {
        file.impl.reset();
    }
    return *this;
}

bool GlobIterator::operator==(GlobIterator const & it) const
{
    return ! file.impl && ! it.file.impl;           // they are equal only at the sentinel value
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
