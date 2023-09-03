struct VertexOutput 
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float diffuse : DIFFUSE;
};


float4 main(VertexOutput input) : SV_TARGET // -> ������� OM���� �����شٴ� ��, symentic name-> ������ ��� �뵵�� ���� �� ��,
{
	//return float4(1.0f, 1.0f, 0.0f, 1.0f); // 1.0f -> UNORM ����
    return input.color;
}