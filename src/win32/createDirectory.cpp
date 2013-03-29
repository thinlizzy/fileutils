#include <Windows.h>
#include "../functions/functions.h"

namespace fs {

Status createDirectory(char const path[])
{
	auto ok = CreateDirectoryA(path,0);
	if( ok ) return Status::ok;
	auto error = GetLastError();
	switch(error) {
		case ERROR_PATH_NOT_FOUND: return failed;
		case ERROR_ALREADY_EXISTS: return ignored;
	}
	return unknown;
}

Status createDirectory(std::string const & path)
{
	return createDirectory(path.c_str());
}

}
