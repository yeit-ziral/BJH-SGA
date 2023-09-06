#include "Framework.h"
#include "Utility.h"

wstring Utility::GetExtension(wstring path)
{
    UINT index = path.find_last_of('.'); // 가장 마지막에 있는 ' ' 안의 값을 찾음

    return path.substr(index + 1, path.length());
}
