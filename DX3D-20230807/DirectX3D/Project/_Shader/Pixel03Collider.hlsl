#include "header.hlsli"

struct VertexOutput
{
    float4 pos : SV_POSITION;
};


float4 main(VertexOutput input) : SV_TARGET // -> ������� OM���� �����شٴ� ��, symentic name-> ������ ��� �뵵�� ���� �� ��,
{
    return mDiffuse;
}