#include "../functions/functions.h"

namespace fs {

PathAndName extractPathAndName(die::NativeString const & path)
{
    auto result = extractPathAndName<wchar_t>(path.wstr);
    return {result.path,result.filename};
}

}


