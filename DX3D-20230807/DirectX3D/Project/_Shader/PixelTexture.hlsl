struct VertexOutput
{
    float4 pos : SV_POSITiON;
    float2 uv : UV;
};

Texture2D map : register(t0);
SamplerState samp : register(s0); // Desc ���� ��, Sampling �� �� �������� ������ ����

float4 main(VertexOutput input) : SV_TARGET 
{
    float4 tex = map.Sample(samp, input.uv);
    
    return tex;
}