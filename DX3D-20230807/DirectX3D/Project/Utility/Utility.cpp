#include "Framework.h"
#include "Utility.h"

wstring Utility::GetExtension(wstring path)
{
    UINT index = path.find_last_of('.'); // 가장 마지막에 있는 ' ' 안의 값을 찾음

    return path.substr(index + 1, path.length());
}

string Utility::ToString(wstring str) // 한글은 wstring에서 1바이트지만 string에서는 2바이트라서 한글은 쓸 수 없음 memcopy를 써서 바꿔줘야 함
{
    string temp;

    temp.assign(str.begin(), str.end());

    return temp;
}

wstring Utility::ToWString(string str)
{
    wstring temp;

    temp.assign(str.begin(), str.end());

    return temp;
}
