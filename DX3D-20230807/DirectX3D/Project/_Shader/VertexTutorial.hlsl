float4 main( float4 pos : POSITION ) : SV_POSITION // symentic -> ������ ��� �뵵�� ���� �� ��,  SV_POSITION (System value position)-> main�� ��ȯ������ ���ϰ��� RS(Rasterizer : �ý���)�� ���ٴ� �� �߰��ܰ��� HS�� TS�� �����ϸ� SV_POSITION�� �ƴ� �ٸ� ���� �� �ش� �߰��ܰ�� ������
{
    float4 a = { 1, 2, 3, 4 };
	
    float4 b = a.xyzw;
    float4 b1 = a.rgba; // hlsl�� �� �� �����ϰ� ��� ���� 
	
	return pos;
}