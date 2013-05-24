#include <Windows.h>
#include "../functions/functions.h"

namespace fs {

Status createDirectory(die::NativeString const & path)
{
    auto ok = CreateDirectoryW(path.wstr.c_str(),0);
    if( ok ) return Status::ok;

    auto error = GetLastError();
    switch(error) {
        case ERROR_PATH_NOT_FOUND: return failed;
        case ERROR_ALREADY_EXISTS: return ignored;
    }
    return unknown;
}

}
