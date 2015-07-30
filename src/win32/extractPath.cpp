#include "../functions/functions.h"

namespace fs {

Filename extractPath(Filename const & path)
{
    return extractPath<wchar_t>(path.wstr);
}

}

