#include "Framework.h"
#include "Utility.h"

wstring Utility::GetExtension(wstring path)
{
    UINT index = path.find_last_of('.'); // ���� �������� �ִ� ' ' ���� ���� ã��

    return path.substr(index + 1, path.length());
}

string Utility::ToString(wstring str) // �ѱ��� wstring���� 1����Ʈ���� string������ 2����Ʈ�� �ѱ��� �� �� ���� memcopy�� �Ἥ �ٲ���� ��
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
