#include "../functions.h"
#include <Windows.h>

namespace fs {

Status createDirectory(char const path[])
{
	auto ok = CreateDirectoryA(path,0);
	if( ok ) return OK;
	auto error = GetLastError();
	switch(error) {
		case ERROR_PATH_NOT_FOUND: return FAILED;
		case ERROR_ALREADY_EXISTS: return IGNORED;
	}
	return UNKNOWN;
}

Status createDirectory(std::string const & path)
{
	return createDirectory(path.c_str());
}

}
