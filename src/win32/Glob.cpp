#include "../classes/GlobIterator.h"
#include <Windows.h>
#include <cstring>
#include <string>
#include <iostream>
#include "UTF8Converters.h"

namespace fs {

class GlobImpl {
	HANDLE handle;
public:
	DWORD lastError;
	WIN32_FIND_DATAW data;

	GlobImpl(char const path[]):
		lastError(0)
	{
		handle = FindFirstFileW(utf8_to_ws(path).c_str(),&data);
		if( invalid() ) {
			lastError = GetLastError();
		}
	}

	~GlobImpl() { FindClose(handle); }

	bool invalid() { return handle == INVALID_HANDLE_VALUE; }

	bool noMoreFiles() { return lastError == ERROR_NO_MORE_FILES; } 

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

std::string GlobFile::filename() const
{
	return wc_to_utf8(impl->data.cFileName);
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
